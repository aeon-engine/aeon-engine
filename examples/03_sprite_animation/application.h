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

#include <aeon/application/desktop_application.h>
#include <aeon/gfx/gfx_frame_listener.h>
#include <aeon/scene/components/orthographic_camera.h>
#include <aeon/scene/components/animated_sprite.h>

enum move_direction : int
{
    move_south = 0,
    move_west = 1,
    move_east = 2,
    move_north = 3
};

class application : public aeon::gfx::frame_listener, public aeon::application::desktop_application
{
public:
    explicit application();
    virtual ~application() = default;

    void main();

private:
    auto on_frame_begin(const float dt) -> bool override;

    std::shared_ptr<aeon::scene::orthographic_camera> camera_;

    std::shared_ptr<aeon::scene::animated_sprite> animated_sprite_;

    float turn_timer_;
    int direction_;
};
