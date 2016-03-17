#include "device.h"
#include "openal/openal_check.h"

#include "codec/audio_codec_wav.h"

namespace aeon
{
namespace audio
{

device::device() :
    device_(nullptr),
    context_(nullptr)
{
    /*!
     * \todo
     * - handle openal extensions (only mono and stereo is guaranteed).
     * - get and log device/vendor name.
     * - get and log openal version.
     */
    const char *device_name = alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);
    printf("aeon::audio::device, device: %s\n", device_name);
    device_ = alcOpenDevice(device_name);
    if (!device_)
        printf("aeon::device, unable to open device\n");

    context_ = alcCreateContext(device_, nullptr);
    if (!context_)
        printf("aeon::device, failed to create context\n");
    
    alcMakeContextCurrent(context_);

    source_manager_ = std::make_shared<aeon::audio::source_manager>();
}

device::~device()
{
    source_manager_.reset();
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context_);
    alcCloseDevice(device_);
}

aeon::audio::source_ptr device::get_source()
{
    auto source = source_manager_->get_source();
    return source;
}

} // namespace audio
} // namespace aeon