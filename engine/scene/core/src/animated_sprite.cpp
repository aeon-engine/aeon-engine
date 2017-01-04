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

#include <aeon/scene/animated_sprite.h>
#include <aeon/scene/sprite_animation_settings.h>

namespace aeon
{
namespace scene
{

animated_sprite::animated_sprite(scene_manager *scene_manager, const std::shared_ptr<gfx::atlas> &atlas, int zorder,
                                 sprite_animation_settings &settings)
    : sprite(scene_manager, atlas, atlas->get_region_by_index(0), settings.size_, zorder)
    , settings_(std::move(settings))
    , frame_time_(0.0f)
    , current_frame_index_(0)
    , running_(false)
    , sequence_(settings_.sequences_.at(settings_.default_sequence_))
{
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

void animated_sprite::set_animation_sequence(const int index)
{
    current_frame_index_ = 0;
    sequence_ = settings_.sequences_.at(index);
}

void animated_sprite::update(const float dt)
{
    frame_time_ += dt;

    auto frame_changed = false;

    while (frame_time_ > settings_.speed_)
    {
        ++current_frame_index_;
        frame_changed = true;
        frame_time_ -= settings_.speed_;
    }

    if (static_cast<std::size_t>(current_frame_index_) >= sequence_.size())
    {
        if (settings_.repeat_ == animation_repeat::once)
            running_ = false;

        current_frame_index_ = 0;
    }

    // TODO: This is highly inefficient. Figure out a better way to do this cleanly.
    if (frame_changed)
        region_ = atlas_->get_region_by_index(sequence_.at(current_frame_index_));

    __generate_and_upload_vertex_data();
}

} // namespace scene
} // namespace aeon
