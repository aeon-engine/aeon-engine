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

#include <aeon/application/desktop_application.h>
#include <aeon/gfx/gfx_frame_listener.h>
#include <aeon/scene/components/orthographic_camera.h>
#include <aeon/input/input_listener.h>

enum class ship_move_direction
{
    none,
    forward,
    reverse
};

enum class ship_rotate_direction
{
    none,
    left,
    right
};

class application : public aeon::application::desktop_application,
                    public aeon::gfx::frame_listener,
                    public aeon::input::input_listener
{
public:
    explicit application();
    virtual ~application() = default;

    void main();

private:
    bool on_frame_begin(const float dt) override;

    void on_keyboard_key_state_changed_event(const aeon::input::keyboard_key key,
                                             const aeon::input::keyboard_key_state key_state,
                                             const int modifier) override;

    void on_mouse_button_event(const aeon::input::mouse_button button,
                               const aeon::input::mouse_button_state button_state) override;

    std::shared_ptr<aeon::scene::orthographic_camera> camera_;

    ship_move_direction move_direction_;
    ship_rotate_direction rotate_direction_;
    float forward_speed_;
    std::shared_ptr<aeon::scene::scene_node> ship_node_;
};
