#pragma once

#include <audio/sample_format.h>
#include <string>

namespace aeon
{
namespace audio
{
class source;
class ibuffer
{
public:
    virtual void load(std::string filename, sample_format format = sample_format::auto_detect) = 0;

    /* prepare function that is always called before the actual play
     * \note i'm still not clear what the final design is, so this is just a
     * intermediate thingy... possibly.
     */
    virtual void prepare() = 0;
    virtual void bind_source(aeon::audio::source *source) = 0;
    virtual void unbind_source(aeon::audio::source *source) = 0;
};

} // namespace audio
} // namespace aeon
