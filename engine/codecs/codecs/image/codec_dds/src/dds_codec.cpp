/*
 * Copyright (c) 2012-2018 Robin Degen
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

#include <aeon/codecs/dds_codec.h>
#include <aeon/streams/memory_stream.h>
#include <aeon/common/compilers.h>
#include <aeon/common/logger.h>

namespace aeon
{
namespace codecs
{

AEON_PACK_STRUCT_PUSH(1)
struct dds_pixelformat
{
    std::uint32_t size;
    std::uint32_t flags;
    std::uint32_t four_cc;
    std::uint32_t rgb_bit_count;
    std::uint32_t r_bit_mask;
    std::uint32_t g_bit_mask;
    std::uint32_t b_bit_mask;
    std::uint32_t a_bit_mask;
} AEON_PACK_STRUCT_POP(1);

AEON_PACK_STRUCT_PUSH(1)
struct dds_header
{
    std::uint32_t size;
    std::uint32_t flags;
    std::uint32_t height;
    std::uint32_t width;
    std::uint32_t pitch_or_linear_size;
    std::uint32_t depth;
    std::uint32_t mipmap_count;
    std::uint32_t reserved1[11];
    dds_pixelformat ddspf;
    std::uint32_t caps;
    std::uint32_t caps2;
    std::uint32_t caps3;
    std::uint32_t caps4;
    std::uint32_t reserved2;
} AEON_PACK_STRUCT_POP(1);

#define MAKE_FOUR_CC(ch0, ch1, ch2, ch3)                                                                               \
    ((std::uint32_t)(std::uint8_t)(ch0) | ((std::uint32_t)(std::uint8_t)(ch1) << 8) |                                  \
     ((std::uint32_t)(std::uint8_t)(ch2) << 16) | ((std::uint32_t)(std::uint8_t)(ch3) << 24))

#define FOURCC_DXT1 (MAKE_FOUR_CC('D', 'X', 'T', '1'))
#define FOURCC_DXT3 (MAKE_FOUR_CC('D', 'X', 'T', '3'))
#define FOURCC_DXT5 (MAKE_FOUR_CC('D', 'X', 'T', '5'))

image_codec_dds::image_codec_dds()
    : logger_(common::logger::get_singleton(), "Codecs::DDSCodec")
{
}

image_codec_dds::~image_codec_dds() = default;

auto image_codec_dds::decode(const std::unique_ptr<resources::resource_provider> &provider) const
    -> std::unique_ptr<resources::image>
{
    AEON_LOG_DEBUG(logger_) << "Decoding DDS image." << std::endl;

    // Check our stream
    if (!provider->good())
    {
        AEON_LOG_ERROR(logger_) << "Could not decode DDS image. Bad stream." << std::endl;
        throw codec_dds_decode_exception();
    }

    auto size = provider->size();

    if (size == 0)
    {
        AEON_LOG_ERROR(logger_) << "Could not decode DDS image. Empty stream." << std::endl;
        throw codec_dds_decode_exception();
    }

    char filecode[4];
    provider->read(reinterpret_cast<std::uint8_t *>(filecode), 4);

    if (strncmp(filecode, "DDS ", 4) != 0)
    {
        AEON_LOG_ERROR(logger_) << "Could not decode DDS image. Invalid file identifier." << std::endl;
        throw codec_dds_decode_exception();
    }

    static_assert(sizeof(dds_header) == 124, "DDS Header must be 124 bytes. Check compiler byte alignment.");

    dds_header header;
    if (provider->read(reinterpret_cast<std::uint8_t *>(&header), sizeof(dds_header)) != sizeof(dds_header))
    {
        AEON_LOG_ERROR(logger_) << "Could not decode DDS image. Could not read header." << std::endl;
        throw codec_dds_decode_exception();
    }

    auto pixel_format = convert_fourcc_to_fixel_format(header.ddspf.four_cc);
    unsigned int block_size = (pixel_format == data::image::pixel_format::dxt1) ? 8 : 16;
    auto image_data_size = ((header.width + 3) / 4) * ((header.height + 3) / 4) * (block_size);
    auto image_data_buffer = std::vector<std::uint8_t>(image_data_size);

    if (provider->read(image_data_buffer.data(), image_data_size) != image_data_size)
    {
        AEON_LOG_ERROR(logger_) << "Could not decode DDS image. Could not read all image data." << std::endl;
        throw codec_dds_decode_exception();
    }

    auto img =
        data::image(std::move(image_data_buffer), header.width, header.height, pixel_format, header.mipmap_count);

    // Create the image object
    return std::make_unique<resources::image>(std::move(img));
}

void image_codec_dds::encode(std::shared_ptr<resources::image> /*source*/,
                             const std::unique_ptr<resources::resource_provider> & /*destination*/) const
{
    AEON_LOG_ERROR(logger_) << "DDS image encoding is not implemented." << std::endl;
    throw codec_dds_encode_exception();
}

auto image_codec_dds::convert_fourcc_to_fixel_format(const std::uint32_t fourcc) const -> data::image::pixel_format
{
    switch (fourcc)
    {
        case FOURCC_DXT1:
            AEON_LOG_DEBUG(logger_) << "Loading image as DXT1." << std::endl;
            return data::image::pixel_format::dxt1;
        case FOURCC_DXT3:
            AEON_LOG_DEBUG(logger_) << "Loading image as DXT3." << std::endl;
            return data::image::pixel_format::dxt3;
        case FOURCC_DXT5:
            AEON_LOG_DEBUG(logger_) << "Loading image as DXT5." << std::endl;
            return data::image::pixel_format::dxt5;
        default:
            AEON_LOG_ERROR(logger_) << "Could not decode DDS image. Invalid or unsupported pixel format: " << fourcc
                                    << std::endl;
            throw codec_dds_decode_exception();
    }
}

} // namespace codecs
} // namespace aeon
