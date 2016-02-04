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

#include <scene/animated_sprite.h>
#include <GL/glew.h>

namespace aeon
{
namespace scene
{
animated_sprite::animated_sprite(scene_manager* scene_manager, gfx::material_ptr texture, glm::vec2 frame_size, int frame_count,
                                 animation_repeat repeat, animation_style style, float animation_speed, int zorder)
    : sprite(scene_manager, texture, frame_size, zorder)
    , frame_count_(frame_count)
    , repeat_(repeat)
    , style_(style)
    , speed_(animation_speed)
    , frame_time_(0.0f)
    , current_frame_(0)
    , sprites_per_row_(0)
{
    glm::vec2 full_size = material_->get_texture()->get_size();
    sprites_per_row_ = static_cast<int>(full_size.x / size_.x);
}

void animated_sprite::render(float dt)
{
    frame_time_ += dt;

    while (frame_time_ > speed_)
    {
        ++current_frame_;
        frame_time_ -= speed_;
    }

    current_frame_ = current_frame_ % frame_count_;

    // TODO: temporary test implementation.
    material_->bind();

    common::types::rectangle<float> uv = __calculate_texture_offset();

    glm::vec2 size_2 = size_ * 0.5f;

    glBegin(GL_QUADS);
    glTexCoord2f(uv.left, uv.bottom);
    glVertex3f(-size_2.x, size_2.y, 0.0f);
    glTexCoord2f(uv.right, uv.bottom);
    glVertex3f(size_2.x, size_2.y, 0.0f);
    glTexCoord2f(uv.right, uv.top);
    glVertex3f(size_2.x, -size_2.y, 0.0f);
    glTexCoord2f(uv.left, uv.top);
    glVertex3f(-size_2.x, -size_2.y, 0.0f);
    glEnd();
}

common::types::rectangle<float> animated_sprite::__calculate_texture_offset()
{
    glm::vec2 full_size = material_->get_texture()->get_size();

    int column = current_frame_ % sprites_per_row_;
    int row = current_frame_ / sprites_per_row_;

    int left_offset = column * static_cast<int>(size_.x);
    int top_offset = row * static_cast<int>(size_.y);

    float left = static_cast<float>(left_offset) / static_cast<float>(full_size.x);
    float right = static_cast<float>(left_offset + size_.x) / static_cast<float>(full_size.x);
    float top = static_cast<float>(top_offset) / static_cast<float>(full_size.y);
    float bottom = static_cast<float>(top_offset + size_.y) / static_cast<float>(full_size.y);

    return { left, top, right, bottom };
}

} // namespace scene
} // namespace aeon
