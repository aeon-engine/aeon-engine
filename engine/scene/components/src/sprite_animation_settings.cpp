/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <aeon/scene/components/sprite_animation_settings.h>

namespace aeon::scene
{

sprite_animation_settings::sprite_animation_settings(const math::vector2<float> frame_size)
    : start_condition_(animation_start_condition::manual_start)
    , repeat_(animation_repeat::continuous)
    , size_(frame_size)
    , speed_(1.0f)
    , default_sequence_(0)
{
}

sprite_animation_settings::sprite_animation_settings(sprite_animation_settings &&other) noexcept
    : start_condition_(std::move(other.start_condition_))
    , repeat_(std::move(other.repeat_))
    , size_(std::move(other.size_))
    , speed_(std::move(other.speed_))
    , sequences_(std::move(other.sequences_))
    , default_sequence_(std::move(other.default_sequence_))
{
}

auto sprite_animation_settings::operator=(sprite_animation_settings &&other) noexcept -> sprite_animation_settings &
{
    start_condition_ = std::move(other.start_condition_);

    repeat_ = std::move(other.repeat_);
    size_ = std::move(other.size_);
    speed_ = std::move(other.speed_);

    sequences_ = std::move(other.sequences_);
    default_sequence_ = std::move(other.default_sequence_);

    return *this;
}

void sprite_animation_settings::generate_sequence(const int index, const int frame_offset, const int frame_count,
                                                  const animation_sequence_type type)
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

void sprite_animation_settings::add_sequence(const int index, const std::vector<int> &seq)
{
    sequences_[index] = seq;
}

void sprite_animation_settings::set_default_sequence(const int index)
{
    default_sequence_ = index;
}

void sprite_animation_settings::set_start_condition(const animation_start_condition condition)
{
    start_condition_ = condition;
}

void sprite_animation_settings::set_repeat(const animation_repeat repeat)
{
    repeat_ = repeat;
}

void sprite_animation_settings::set_speed(const float speed)
{
    speed_ = speed;
}

void sprite_animation_settings::__generate_normal_sequence(const int index, const int frame_offset,
                                                           const int frame_count)
{
    auto seq = std::vector<int>();
    for (auto i = 0; i < frame_count; ++i)
        seq.push_back(i + frame_offset);

    sequences_[index] = seq;
}

void sprite_animation_settings::__generate_reverse_sequence(const int index, const int frame_offset,
                                                            const int frame_count)
{
    auto seq = std::vector<int>();
    for (auto i = 1; i <= frame_count; ++i)
        seq.push_back((frame_count - i) + frame_offset);

    sequences_[index] = seq;
}

void sprite_animation_settings::__generate_up_down_sequence(const int index, const int frame_offset,
                                                            const int frame_count)
{
    auto seq = std::vector<int>();
    for (auto i = 0; i < frame_count; ++i)
        seq.push_back(i + frame_offset);

    for (auto i = frame_count - 2; i != 0; --i)
        seq.push_back(i + frame_offset);

    sequences_[index] = seq;
}
} // namespace aeon::scene
