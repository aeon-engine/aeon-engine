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
#include <aeon/utility.h>
#include <resources/resource_manager.h>
#include <resources/codecs/sound_codec.h>
#include <resources/wrappers/sound_resource_wrapper.h>
#include <common/buffer.h>
#include <audio/audio.h>

namespace aeon
{
namespace resources
{

sound_codec::sound_codec()
    : logger_(common::logger::get_singleton(), "Resources::SoundCodec")
{
}

resource_encoding sound_codec::get_codec_type() const
{
    return resource_encoding::sound_ogg;
}

audio::sound_ptr sound_codec::decode(resource_manager & /*parent*/, sound_resource_wrapper_ptr wrapper)
{
    AEON_LOG_DEBUG(logger_) << "Decoding sound resource." << std::endl;

    common::buffer_u8 input;
    wrapper->read_raw(input);

    aeon::audio::buffer_static_ptr buffer = std::make_shared<aeon::audio::buffer_static>();
    buffer->load(input);
    return buffer;
}

aeon::audio::stream_ptr sound_codec::open_stream(resource_manager & /*parent*/, stream_resource_wrapper_ptr wrapper)
{
    AEON_LOG_DEBUG(logger_) << "Decoding audio stream resource." << std::endl;

    common::buffer_u8 input;
    wrapper->read_raw(input);

    aeon::audio::buffer_streaming_ptr buffer = std::make_shared<aeon::audio::buffer_streaming>();
    buffer->load(input);
    return buffer;
}

} // namespace resources
} // namespace aeon
