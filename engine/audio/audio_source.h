#pragma once

#include <audio/audio_buffer.h>

#include <audio/openal/openal_includes.h>

#include <memory>
#include <glm/vec3.hpp>

namespace aeon
{
namespace audio
{

enum class source_status : int
{
    stopped,
    paused,
    playing,
};

class source_manager;
class source
{
public:
    source();
    virtual ~source();

    // setters, we ignore the need for getters now...
    void set_pitch(float pitch);
    void set_gain(float gain);
    void set_position(glm::vec3 &position);

    void play();
    void pause();
    void stop();

    /*!
     * Bind an audio buffer to this source, currently we only deal with static
     * buffers. This means that an aeon::audio::source can only be binded to
     * a single aeon::audio::buffer.
     *
     * \note In the future we will add support for audio streams, this will
     *       cause a aeon::audio::source to maybe contain multiple buffers.
     */
    void bind(aeon::audio::buffer_ptr buffer);


    /*!
     * Unbind audio buffer from this source, this function is usually called
     * from the binded audio buffer object.
     *
     * \note I am aware this is a hack, but in openal you have to stop & unbind
     *       any source that is binded to the buffer before you can uninitialize
     *       the openal buffer.
     */
    void unbind();

    // getters
    source_status get_status();

    // this is a hack
    ALuint get_al_source();

private:
    ALuint source_;
    aeon::audio::buffer_ptr buffer_;
};

using source_ptr = std::shared_ptr<source>;


} // namespace audio
} // namespace aeon
