#pragma once

#include <audio/audio_sample_buffer.h>
#include <audio/audio_source_manager.h>
#include <audio/openal/openal_includes.h>

#include <string>
#include <list>

namespace aeon
{
namespace audio
{
class device
{
public:
    device();
    ~device();

    aeon::audio::source_ptr get_source();

protected:
    std::list<sample_buffer_ptr> sample_list_;
    std::shared_ptr<aeon::audio::source_manager> source_manager_;

private:
    ALCdevice *device_;
    ALCcontext *context_;
};

} // namespace audio
} // namespace aeon
