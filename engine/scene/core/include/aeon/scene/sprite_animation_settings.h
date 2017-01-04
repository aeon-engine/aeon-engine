/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#pragma once

#include <aeon/utility.h>
#include <aeon/scene/sprite.h>
#include <aeon/common/types/rectangle.h>
#include <map>
#include <vector>
#include <memory>

namespace aeon
{
namespace scene
{

enum class animation_start_condition
{
    auto_start,
    manual_start
};

enum class animation_repeat
{
    once,
    continuous
};

enum class animation_sequence_type
{
    normal,
    reverse,
    up_down
};

class sprite_animation_settings : utility::noncopyable
{
    friend class animated_sprite;

public:
    explicit sprite_animation_settings(const glm::vec2 frame_size);
    ~sprite_animation_settings() = default;

    sprite_animation_settings(sprite_animation_settings &&other) noexcept;
    sprite_animation_settings &operator=(sprite_animation_settings &&other) noexcept;

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
    glm::vec2 size_;
    float speed_;

    std::map<int, std::vector<int>> sequences_;
    int default_sequence_;
};

} // namespace scene
} // namespace aeon
