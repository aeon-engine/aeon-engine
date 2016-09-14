#include <audio/audio_source.h>
#include <audio/audio_source_manager.h>
#include <audio/audio_buffer_static.h>
#include <audio/audio_buffer_streaming.h>
#include <audio/openal/openal_check.h>

namespace aeon
{
namespace audio
{

source::source()
    : source_(0)
    , buffer_(nullptr)
{
    al_check(alGenSources(1, &source_));
    al_check(alSourcei(source_, AL_BUFFER, 0));
}

source::~source()
{
    stop();
    al_check(alSourcei(source_, AL_BUFFER, 0));
    al_check(alDeleteSources(1, &source_));
}

void source::set_pitch(float pitch)
{
    al_check(alSourcef(source_, AL_PITCH, pitch));
}

void source::set_gain(float gain)
{
    al_check(alSourcef(source_, AL_GAIN, gain));
}

void source::set_position(glm::vec3 &position)
{
    // \note I dono if we can convert from 3d engine space directly to audio space...
    al_check(alSource3f(source_, AL_POSITION, position.x, position.y, position.z));
}

void source::bind(aeon::audio::buffer_ptr buffer)
{
    buffer_ = buffer;

    /* the actual 'openal' bind between source and buffer occurs inside the
     * buffer bind_source function
     */
    buffer_->bind_source(this);
}

void source::unbind()
{
    stop();

    buffer_->unbind_source(this);

    buffer_ = nullptr;
}

void source::play()
{
    if (buffer_ != nullptr)
        buffer_->prepare();

    set_gain(1.f);
    set_pitch(1.f);

    al_check(alSourcePlay(source_));
}

void source::pause()
{
    al_check(alSourcePause(source_));
}

void source::stop()
{
    al_check(alSourceStop(source_));
}

source_status source::get_status()
{
    ALint status;
    al_check(alGetSourcei(source_, AL_SOURCE_STATE, &status));

    switch (status)
    {
        case AL_INITIAL:
        case AL_STOPPED:
            return source_status::stopped;
        case AL_PAUSED:
            return source_status::paused;
        case AL_PLAYING:
            return source_status::playing;
    }

    printf("aeon::audio::source, unknown source status\n");
    return source_status::stopped;
}

ALuint source::get_al_source()
{
    return source_;
}

} // namespace audio
} // namespace aeon
