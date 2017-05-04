/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <aeon/codecs/png_read_structs.h>
#include <aeon/codecs/png_codec.h>
#include <aeon/streams/memory_stream.h>
#include <aeon/common/noncopyable.h>
#include <aeon/common/compilers.h>
#include <aeon/common/logger.h>
#include <png.h>
#include <array>

#define PNG_HEADER_SIGNATURE_SIZE 8

namespace aeon
{
namespace codecs
{

static void __png_read_callback(png_structp png_ptr, png_bytep output_ptr, png_size_t output_size)
{
    // TODO: Find a better way to do this
    auto logger = logger::logger(common::logger::get_singleton(), "Codecs::PNGCodec");

    auto stream = static_cast<streams::stream *>(png_get_io_ptr(png_ptr));

    // Do we have a stream?
    if (!stream)
    {
        AEON_LOG_ERROR(logger) << "Could not decode PNG image. Invalid stream in read callback." << std::endl;
        throw codec_png_decode_exception();
    }

    // Read the data
    if (stream->read(output_ptr, static_cast<size_t>(output_size)) != output_size)
    {
        AEON_LOG_ERROR(logger) << "Could not decode PNG image. Could not read the requested data from stream."
                               << std::endl;
        throw codec_png_decode_exception();
    }
}

image_codec_png::image_codec_png()
    : logger_(common::logger::get_singleton(), "Codecs::PNGCodec")
{
}

auto image_codec_png::decode(const std::unique_ptr<resources::resource_provider> &provider) const
    -> std::unique_ptr<resources::image>
{
    AEON_LOG_DEBUG(logger_) << "Decoding PNG image." << std::endl;

    auto input = std::vector<std::uint8_t>();
    provider->read(input);

    auto stream = streams::memory_stream(std::move(input), aeon::streams::access_mode::read);

    // Check our stream
    if (!stream.good())
    {
        AEON_LOG_ERROR(logger_) << "Could not decode PNG image. Bad stream." << std::endl;
        throw codec_png_decode_exception();
    }

    auto size = stream.size();

    if (size == 0)
    {
        AEON_LOG_ERROR(logger_) << "Could not decode PNG image. Empty stream." << std::endl;
        throw codec_png_decode_exception();
    }

    // Read the header
    auto png_header = std::array<png_byte, PNG_HEADER_SIGNATURE_SIZE>();
    stream.read(png_header.data(), PNG_HEADER_SIGNATURE_SIZE);

    // Check the header
    if (png_sig_cmp(png_header.data(), 0, PNG_HEADER_SIGNATURE_SIZE))
    {
        AEON_LOG_ERROR(logger_) << "Could not decode PNG image. Invalid signature." << std::endl;
        throw codec_png_decode_exception();
    }

    auto png_structs = png_read_structs(logger_);

    // Bind errors from libpng
    AEON_IGNORE_VS_WARNING_PUSH(4611)
    if (setjmp(png_jmpbuf(png_structs.png_ptr())))
    {
        AEON_LOG_ERROR(logger_) << "Could not decode PNG image. Error reported by libpng while decoding." << std::endl;
        throw codec_png_decode_exception();
    }
    AEON_IGNORE_VS_WARNING_POP()

    // Init png reading. We will be using a read function, as we can't read
    // from a file.
    png_set_read_fn(png_structs.png_ptr(), &stream, __png_read_callback);

    // Let libpng know we already read the signature
    png_set_sig_bytes(png_structs.png_ptr(), PNG_HEADER_SIGNATURE_SIZE);

    // Read all the info up to the image data
    png_read_info(png_structs.png_ptr(), png_structs.info_ptr());

    // Variables to pass to get info
    auto bit_depth = 0;
    auto color_type = 0;
    auto temp_width = png_uint_32();
    auto temp_height = png_uint_32();

    // Get info about png
    png_get_IHDR(png_structs.png_ptr(), png_structs.info_ptr(), &temp_width, &temp_height, &bit_depth, &color_type,
                 nullptr, nullptr, nullptr);

    auto pixel_format = convert_color_type_to_pixel_format(color_type);

    // Update the png info struct.
    png_read_update_info(png_structs.png_ptr(), png_structs.info_ptr());

    auto rowbytes = png_get_rowbytes(png_structs.png_ptr(), png_structs.info_ptr());

    // Allocate the image_data as a big block
    auto bitmap_buff_size = rowbytes * temp_height * sizeof(png_byte);

    auto bitmap_buffer = std::vector<std::uint8_t>(bitmap_buff_size);

    // Cast to png_byte since this is what libpng likes as buffer.
    // Just passing the pointer should be fine. But this ensures 100%
    // compatibility.
    auto image_data = static_cast<png_byte *>(&(bitmap_buffer)[0]);

    // Row_pointers is for pointing to image_data for reading the
    // png with libpng
    auto rowpointer_buff_size = temp_height * sizeof(png_bytep);
    auto rowpointer_buffer = std::vector<std::uint8_t *>(rowpointer_buff_size);

    // Cast to png_bytep
    auto row_pointers = static_cast<png_bytep *>(&(rowpointer_buffer)[0]);

    // Set the individual row_pointers to point at the correct offsets
    // of image_data
    for (auto i = 0ul; i < temp_height; ++i)
    {
        row_pointers[i] = image_data + i * rowbytes;
    }

    // Read the png into image_data through row_pointers
    png_read_image(png_structs.png_ptr(), row_pointers);

    auto img = data::image(std::move(bitmap_buffer), temp_width, temp_height, pixel_format);

    // Create the image object
    return std::make_unique<resources::image>(std::move(img));
}

auto image_codec_png::convert_color_type_to_pixel_format(const int color_type) const -> data::image::pixel_format
{
    switch (color_type)
    {
        case PNG_COLOR_TYPE_RGB:
            AEON_LOG_DEBUG(logger_) << "Loading image as RGB." << std::endl;
            return data::image::pixel_format::rgb;
        case PNG_COLOR_TYPE_RGB_ALPHA:
            AEON_LOG_DEBUG(logger_) << "Loading image as RGBA." << std::endl;
            return data::image::pixel_format::rgba;
        default:
            AEON_LOG_ERROR(logger_) << "Could not decode PNG image. Invalid or unsupported pixel format: " << color_type
                                    << std::endl;
            throw codec_png_decode_exception();
    }
}

} // namespace codecs
} // namespace aeon
