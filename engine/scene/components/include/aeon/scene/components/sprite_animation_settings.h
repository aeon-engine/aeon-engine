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

#pragma once

#include <aeon/scene/components/sprite.h>
#include <map>
#include <vector>
#include <cstdint>

namespace aeon::scene
{

enum class animation_start_condition : std::uint32_t
{
    auto_start = 0,
    manual_start
};

enum class animation_repeat : std::uint32_t
{
    once = 0,
    continuous
};

enum class animation_sequence_type : std::uint32_t
{
    normal = 0,
    reverse,
    up_down
};

class sprite_animation_settings
{
    friend class animated_sprite;

public:
    explicit sprite_animation_settings(const math::vector2<float> frame_size);
    ~sprite_animation_settings() = default;

    sprite_animation_settings(const sprite_animation_settings &) noexcept = delete;
    auto operator=(const sprite_animation_settings &) noexcept -> sprite_animation_settings & = delete;

    sprite_animation_settings(sprite_animation_settings &&) noexcept;
    auto operator=(sprite_animation_settings &&) noexcept -> sprite_animation_settings &;

    void generate_sequence(const int index, const int frame_offset, const int frame_count,
                           const animation_sequence_type type);
    void add_sequence(const int index, const std::vector<int> &seq);

    void set_default_sequence(const int index);

    void set_start_condition(const animation_start_condition condition);
    void set_repeat(const animation_repeat repeat);

    void set_speed(const float speed);

private:
    void __generate_normal_sequence(const int index, const int frame_offset, const int frame_count);
    void __generate_reverse_sequence(const int index, const int frame_offset, const int frame_count);
    void __generate_up_down_sequence(const int index, const int frame_offset, const int frame_count);

    animation_start_condition start_condition_;
    animation_repeat repeat_;
    math::vector2<float> size_;
    float speed_;

    std::map<int, std::vector<int>> sequences_;
    int default_sequence_;
};

} // namespace aeon::scene
