/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#include <buildconfig.h>

#ifdef AEON_USE_PNG

#include <aeon/streams.h>
#include <resources/codecs/image_png_codec.h>
#include <resources/wrappers/image_resource_wrapper.h>
#include <common/buffer.h>
#include <png.h>

#define PNG_HEADER_SIGNATURE_SIZE 8
#include <console/console.h>

namespace aeon
{
namespace resources
{

// RAII wrapper for png_destroy_read_struct
class png_read_structs
{
public:
    png_read_structs() :
        png_ptr_(nullptr),
        info_ptr_(nullptr),
        end_info_(nullptr)
    {
        // Create the read struct for PNG
        png_ptr_ = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

        if (!png_ptr_)
            throw codec_png_decode_exception();

        // Create png info struct
        info_ptr_ = png_create_info_struct(png_ptr_);

        if (!info_ptr_)
            throw codec_png_decode_exception();

        // Create png end info struct
        end_info_ = png_create_info_struct(png_ptr_);

        if (!end_info_)
            throw codec_png_decode_exception();
    }

    ~png_read_structs()
    {
        // TODO: What happens if png_create_read_struct fails?
        // Can we call png_destroy_read_struct with null pointers?
        // This is unclear in the PNG documentation and examples.
        // Does this mean we leak memory in that case?
        if (png_ptr_ && info_ptr_ && end_info_)
        {
            png_destroy_read_struct(&png_ptr_, &info_ptr_, &end_info_);
        }

        png_ptr_ = nullptr;
        info_ptr_ = nullptr;
        end_info_ = nullptr;
    }

    png_structp png_ptr() const { return png_ptr_; }
    png_infop info_ptr() const { return info_ptr_; }
    png_infop end_info() const { return end_info_; }

private:
    png_structp png_ptr_;
    png_infop info_ptr_;
    png_infop end_info_;
};

static void __png_read_callback(png_structp png_ptr, png_bytep output_ptr, png_size_t output_size)
{
    aeon::streams::stream *stream = static_cast<aeon::streams::stream *>(png_get_io_ptr(png_ptr));

    // Do we have a stream?
    if (!stream)
        throw codec_png_decode_exception();

    // Read the data
    if (stream->read(output_ptr, static_cast<size_t>(output_size)) != output_size)
        throw codec_png_decode_exception();
}

image_codec_png::image_codec_png()
{

}

image_codec_png::~image_codec_png()
{

}

image_ptr image_codec_png::decode(image_resource_wrapper &wrapper)
{
    common::buffer_u8 input;
    wrapper.read_raw(input);

    aeon::streams::memory_stream stream(std::move(input), aeon::streams::access_mode::read);

    // Check our stream
    if (!stream.good())
        throw codec_png_decode_exception();

    size_t size = stream.size();

    if (size == 0)
        throw codec_png_decode_exception();

    // Read the header
    png_byte png_header[PNG_HEADER_SIGNATURE_SIZE];
    stream.read(png_header, PNG_HEADER_SIGNATURE_SIZE);

    // Check the header
    if (png_sig_cmp(png_header, 0, PNG_HEADER_SIGNATURE_SIZE))
        throw codec_png_decode_exception();

    png_read_structs png_structs;

    // Bind errors from libpng
    if (setjmp(png_jmpbuf(png_structs.png_ptr())))
        throw codec_png_decode_exception();

    // Init png reading. We will be using a read function, as we can't read
    // from a file.
    png_set_read_fn(png_structs.png_ptr(), &stream, __png_read_callback);

    // Let libpng know we already read the signature
    png_set_sig_bytes(png_structs.png_ptr(), PNG_HEADER_SIGNATURE_SIZE);

    // Read all the info up to the image data
    png_read_info(png_structs.png_ptr(), png_structs.info_ptr());

    // Variables to pass to get info
    int bit_depth, color_type;
    png_uint_32 temp_width, temp_height;

    // Get info about png
    png_get_IHDR(png_structs.png_ptr(), png_structs.info_ptr(), &temp_width, &temp_height, &bit_depth,
        &color_type, nullptr, nullptr, nullptr);

    image::pixel_format pixel_format = image::pixel_format::rgba;
    // Check the pixel format
    switch (color_type)
    {
        case PNG_COLOR_TYPE_RGB:
            pixel_format = image::pixel_format::rgb;
            break;
        case PNG_COLOR_TYPE_RGB_ALPHA:
            pixel_format = image::pixel_format::rgba;
            break;
        default:
            throw codec_png_decode_exception();
    }

    // Update the png info struct.
    png_read_update_info(png_structs.png_ptr(), png_structs.info_ptr());

    size_t rowbytes = png_get_rowbytes(png_structs.png_ptr(), png_structs.info_ptr());

    // Allocate the image_data as a big block
    size_t bitmap_buff_size = rowbytes * size_t(temp_height) * sizeof(png_byte);

    common::buffer_u8 bitmap_buffer(bitmap_buff_size);

    // Cast to png_byte since this is what libpng likes as buffer.
    // Just passing the pointer should be fine. But this ensures 100%
    // compatibility.
    png_byte * image_data = static_cast<png_byte *>(&(bitmap_buffer)[0]);

    // Row_pointers is for pointing to image_data for reading the
    // png with libpng
    size_t rowpointer_buff_size = size_t(temp_height) * sizeof(png_bytep);
    common::buffer_pu8 rowpointer_buffer(rowpointer_buff_size);

    // Cast to png_bytep
    png_bytep * row_pointers = static_cast<png_bytep *>(&(rowpointer_buffer)[0]);

    // Set the individual row_pointers to point at the correct offsets
    // of image_data
    for (size_t i = 0; i < size_t(temp_height); i++)
    {
        row_pointers[i] = image_data + i * rowbytes;
    }

    // Read the png into image_data through row_pointers
    png_read_image(png_structs.png_ptr(), row_pointers);

    // Create the image object
    return std::make_shared<image>(
        wrapper,
        std::move(bitmap_buffer),
        temp_width,
        temp_height,
        pixel_format
    );
}

resource_encoding image_codec_png::get_codec_type() const
{
    return resource_encoding::image_png;
}

} // namespace resources
} // namespace aeon

#endif // AEON_USE_PNG
