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
#include <scene/sprite_animation_settings.h>
#include <GL/glew.h>

namespace aeon
{
namespace scene
{

animated_sprite::animated_sprite(scene_manager* scene_manager, sprite_batch_ptr batch, gfx::material_ptr texture,
                                 int zorder, const sprite_animation_settings &settings)
    : sprite(scene_manager, batch, texture, settings.size_, zorder)
    , settings_(settings)
    , frame_time_(0.0f)
    , current_frame_index_(0)
    , sprites_per_row_(0)
    , running_(false)
    , sequence_(settings_.sequences_.at(settings_.default_sequence_))
{
    glm::vec2 full_size = material_->get_texture()->get_size();
    sprites_per_row_ = static_cast<int>(full_size.x / size_.x);

    if (settings_.start_condition_ == animation_start_condition::auto_start)
        running_ = true;
}

void animated_sprite::run()
{
    running_ = true;
}

void animated_sprite::stop()
{
    running_ = false;
}

void animated_sprite::set_animation_sequence(int index)
{
    current_frame_index_ = 0;
    sequence_ = settings_.sequences_.at(index);
}

void animated_sprite::__set_next_frame(float dt)
{
    frame_time_ += dt;

    while (frame_time_ > settings_.speed_)
    {
        ++current_frame_index_;
        frame_time_ -= settings_.speed_;
    }

    if (current_frame_index_ >= sequence_.size())
    {
        if (settings_.repeat_ == animation_repeat::once)
            running_ = false;

        current_frame_index_ = 0;
    }
}

common::types::rectangle<float> animated_sprite::__calculate_texture_offset()
{
    glm::vec2 full_size = material_->get_texture()->get_size();

    int current_frame = sequence_[current_frame_index_];

    int column = current_frame % sprites_per_row_;
    int row = current_frame / sprites_per_row_;

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
