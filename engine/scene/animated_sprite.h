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

#pragma once

#include <scene/sprite.h>
#include <common/types/rectangle.h>
#include <memory>

namespace aeon
{
namespace scene
{

enum class animation_repeat
{
    once,
    continuous
};

enum class animation_style
{
    normal
};

class animated_sprite : public sprite
{
public:
    explicit animated_sprite(scene_manager* scene_manager, gfx::material_ptr texture, glm::vec2 frame_size, int frame_count,
        animation_repeat repeat, animation_style style, float animation_speed, int zorder);

    virtual ~animated_sprite() = default;

private:
    void render(float dt) override;

    common::types::rectangle<float> __calculate_texture_offset();

    int frame_count_;
    animation_repeat repeat_;
    animation_style style_;
    float speed_;
    float frame_time_;
    int current_frame_;
    int sprites_per_row_;
};

using animated_sprite_ptr = std::shared_ptr<animated_sprite>;

} // namespace scene
} // namespace aeon
