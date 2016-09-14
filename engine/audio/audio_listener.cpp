#include <audio/audio_listener.h>
#include <audio/openal/openal_includes.h>
#include <audio/openal/openal_check.h>

namespace aeon
{
namespace audio
{

listener::listener()
{
    // set the distance unit to 1 cm (is a openal extention?)
    set_distance_unit(0.01f);
}

void listener::set_distance_unit(float meters /*= 0.01f*/)
{
    al_check(alListenerf(AL_METERS_PER_UNIT, meters));
}

void listener::set_gain(float gain)
{
    al_check(alListenerf(AL_GAIN, gain));
}

void listener::set_position(glm::vec3 &position)
{
    al_check(alListener3f(AL_POSITION, position.x, position.y, position.z));
}

void listener::set_direction(glm::vec3 &direction)
{
    float orientation[] = {direction.x, direction.y, direction.z, 0.f, 1.f, 0.f};
    al_check(alListenerfv(AL_ORIENTATION, orientation));
}

} // namespace audio
} // namespace aeon