/*
 * Copyright (c) 2012-2017 Robin Degen
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

#include <aeon/scene/components/animated_sprite.h>
#include <aeon/scene/components/sprite_animation_settings.h>

namespace aeon
{
namespace scene
{

animated_sprite::animated_sprite(scene_manager &scene_manager, const std::shared_ptr<gfx::atlas> &atlas, int zorder,
                                 sprite_animation_settings &settings, const std::string &name)
    : sprite(scene_manager, atlas, atlas->get_region_by_index(0), settings.size_, zorder, name)
    , settings_(std::move(settings))
    , frame_time_(0.0f)
    , current_frame_index_(0)
    , running_(false)
    , sequence_(settings_.sequences_.at(settings_.default_sequence_))
{
    region_ = atlas_->get_region_by_index(sequence_.at(current_frame_index_));

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
    auto frame_changed = false;

    if (running_)
    {
        frame_time_ += dt;
        while (frame_time_ > settings_.speed_)
        {
            ++current_frame_index_;
            frame_changed = true;
            frame_time_ -= settings_.speed_;
        }
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
