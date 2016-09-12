/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
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

#include <aeon/platform.h>
#include <aeon/streams.h>
#include <resources/codecs/tga/image_tga_codec.h>
#include <resources/wrappers/image_resource_wrapper.h>
#include <common/buffer.h>
#include <tga.h>

namespace aeon
{
namespace resources
{

static int tga_stream_fgetc(TGA *tga)
{
    streams::memory_stream &memory_stream = *reinterpret_cast<streams::memory_stream *>(tga->fd);
    std::uint8_t c;
    memory_stream.read(&c, 1);
	return static_cast<int>(c);
}

static size_t tga_stream_fread(TGA *tga, void *buffer, size_t size, size_t count)
{
    streams::memory_stream &memory_stream = *reinterpret_cast<streams::memory_stream *>(tga->fd);
    memory_stream.read(static_cast<std::uint8_t *>(buffer), size * count);
	return 0;
}

static int tga_stream_fputc(TGA *tga, int c)
{
    throw codec_tga_decode_exception();
}

static size_t tga_stream_fwrite(TGA *tga, const void* buffer, size_t size, size_t count)
{
    throw codec_tga_decode_exception();
}

static void tga_stream_fseek(TGA *tga, long offset, int origin)
{
    streams::memory_stream &memory_stream = *reinterpret_cast<streams::memory_stream *>(tga->fd);
	
    streams::stream::seek_direction direction;
    switch (origin)
    {
        case SEEK_SET:
            direction = streams::stream::seek_direction::begin;
            break;
        case SEEK_CUR:
            direction = streams::stream::seek_direction::current;
            break;
        case SEEK_END:
            direction = streams::stream::seek_direction::end;
            break;
        default:
            throw codec_tga_decode_exception();
    }
    
    memory_stream.seek(offset, direction);
}

static long tga_stream_ftell(TGA *tga)
{
    // Since ftell is only used when opening the file, we can safely return 0 here.
    return 0;
}

static void tga_free_data(TGAData *data)
{
    free(data->cmap);
    free(data->img_data);
    free(data->img_id);
}

image_codec_tga::image_codec_tga()
    : logger_(common::logger::get_singleton(), "Resources::TGACodec")
{
}

image_ptr image_codec_tga::decode(resource_manager & /*parent*/, image_resource_wrapper_ptr wrapper)
{
    AEON_LOG_DEBUG(logger_) << "Decoding TGA image resource." << std::endl;

    common::buffer_u8 input;
    wrapper->read_raw(input);

    streams::memory_stream stream(std::move(input), aeon::streams::access_mode::read);

    // Check our stream
    if (!stream.good())
    {
        AEON_LOG_ERROR(logger_) << "Could not decode TGA image. Bad stream." << std::endl;
        throw codec_png_decode_exception();
    }

    size_t size = stream.size();

    if (size == 0)
    {
        AEON_LOG_ERROR(logger_) << "Could not decode TGA image. Empty stream." << std::endl;
        throw codec_png_decode_exception();
    }

    TGA *tga = TGAOpenUserDef(reinterpret_cast<void *>(&stream), tga_stream_fgetc, tga_stream_fread, tga_stream_fputc,
        tga_stream_fwrite, tga_stream_fseek, tga_stream_ftell);

    TGAData data { nullptr, nullptr, nullptr, 0};

    TGAReadImage(tga, &data);
    if (tga->last != TGA_OK)
        throw codec_png_decode_exception();

    tga_free_data(&data);
    TGAClose(tga);

    //data::image img(std::move(bitmap_buffer), static_cast<unsigned int>(tga->hdr.width), static_cast<unsigned int>(tga->hdr.height), pixel_format);

    // Create the image object
    return nullptr; //std::make_shared<image>(wrapper, std::move(img));
}

resource_encoding image_codec_tga::get_codec_type() const
{
    return resource_encoding::image_tga;
}

} // namespace resources
} // namespace aeon
