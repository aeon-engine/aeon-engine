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

#include <scene/sprite_animation_settings.h>

namespace aeon
{
namespace scene
{

sprite_animation_settings::sprite_animation_settings(glm::vec2 frame_size)
    : start_condition_(animation_start_condition::manual_start)
    , repeat_(animation_repeat::continuous)
    , size_(frame_size)
    , speed_(1.0f)
    , default_sequence_(0)
{
}

void sprite_animation_settings::generate_sequence(int index, int frame_offset, int frame_count,
                                                  animation_sequence_type type)
{
    switch (type)
    {
        case animation_sequence_type::normal:
        {
            __generate_normal_sequence(index, frame_offset, frame_count);
        }
        break;
        case animation_sequence_type::reverse:
        {
            __generate_reverse_sequence(index, frame_offset, frame_count);
        }
        break;
        case animation_sequence_type::up_down:
        {
            __generate_up_down_sequence(index, frame_offset, frame_count);
        }
        break;
        default:
        {
            sequences_[index] = {0};
        }
        break;
    }
}

void sprite_animation_settings::add_sequence(int index, std::vector<int> seq)
{
    sequences_[index] = seq;
}

void sprite_animation_settings::set_default_sequence(int index)
{
    default_sequence_ = index;
}

void sprite_animation_settings::set_start_condition(animation_start_condition condition)
{
    start_condition_ = condition;
}

void sprite_animation_settings::set_repeat(animation_repeat repeat)
{
    repeat_ = repeat;
}

void sprite_animation_settings::set_speed(float speed)
{
    speed_ = speed;
}

void sprite_animation_settings::__generate_normal_sequence(int index, int frame_offset, int frame_count)
{
    std::vector<int> seq;
    for (int i = 0; i < frame_count; ++i)
        seq.push_back(i + frame_offset);

    sequences_[index] = seq;
}

void sprite_animation_settings::__generate_reverse_sequence(int index, int frame_offset, int frame_count)
{
    std::vector<int> seq;
    for (int i = 1; i <= frame_count; ++i)
        seq.push_back((frame_count - i) + frame_offset);

    sequences_[index] = seq;
}

void sprite_animation_settings::__generate_up_down_sequence(int index, int frame_offset, int frame_count)
{
    std::vector<int> seq;
    for (int i = 0; i < frame_count; ++i)
        seq.push_back(i + frame_offset);

    for (int i = frame_count - 2; i != 0; --i)
        seq.push_back(i + frame_offset);

    sequences_[index] = seq;
}

} // namespace scene
} // namespace aeon
