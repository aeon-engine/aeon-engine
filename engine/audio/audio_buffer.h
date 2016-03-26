#pragma once

#include <audio/audio_sample_format.h>
#include <common/buffer.h>

#include <string>
#include <memory>

namespace aeon
{
namespace audio
{
class source;
class buffer
{
public:
    buffer() = default;
    virtual ~buffer() = default;

    virtual void load(std::string filename, sample_format format = sample_format::auto_detect) = 0;
    virtual void load(common::buffer_u8 &data, sample_format format = sample_format::auto_detect) = 0;

    /* prepare function that is always called before the actual play
     * \note i'm still not clear what the final design is, so this is just a
     * intermediate thingy... possibly.
     */
    virtual void prepare() = 0;
    virtual void bind_source(aeon::audio::source *source) = 0;
    virtual void unbind_source(aeon::audio::source *source) = 0;
};

using buffer_ptr = std::shared_ptr<audio::buffer>;
using sound_ptr = buffer_ptr;
using stream_ptr = buffer_ptr;

} // namespace audio
} // namespace aeon
