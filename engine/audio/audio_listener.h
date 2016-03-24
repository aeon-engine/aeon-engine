#pragma once

#include <glm/vec3.hpp>

namespace aeon
{
namespace audio
{
/* \note it seems that in openal there can be only 1 listener? */
class listener
{
public:
    listener();

    void set_distance_unit(float meters = 0.01f);
    void set_gain(float gain);
    void set_position(glm::vec3 &position);
    void set_direction(glm::vec3 &direction);
};

} // namespace audio
} // namespace aeon
