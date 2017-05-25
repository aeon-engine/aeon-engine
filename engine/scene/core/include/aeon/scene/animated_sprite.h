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

#pragma once

#include <aeon/scene/sprite.h>
#include <aeon/common/types/rectangle.h>
#include <aeon/scene/sprite_animation_settings.h>
#include <aeon/gfx/gfx_atlas.h>
#include <memory>

namespace aeon
{
namespace scene
{

class animated_sprite : public sprite
{
public:
    explicit animated_sprite(scene_manager &scene_manager, const std::shared_ptr<gfx::atlas> &atlas, int zorder,
                             sprite_animation_settings &settings, const std::string &name = "");

    virtual ~animated_sprite() = default;

    void run();
    void stop();

    void set_animation_sequence(const int index);

protected:
    void update(const float dt) override;

    sprite_animation_settings settings_;

    float frame_time_;
    int current_frame_index_;
    bool running_;

    std::vector<int> sequence_;
};

} // namespace scene
} // namespace aeon
