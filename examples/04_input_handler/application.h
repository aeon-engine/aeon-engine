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

#include <application/desktop_application.h>
#include <aeon/gfx/gfx_frame_listener.h>
#include <aeon/resources/wrappers/image_resource_wrapper.h>
#include <aeon/scene/basic_scene_manager/basic_scene_manager.h>
#include <aeon/scene/orthographic_camera.h>
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

class application : public aeon::desktop_application<aeon::scene::basic_scene_manager>,
                    public aeon::gfx::frame_listener,
                    public aeon::input::input_listener
{
public:
    explicit application();
    virtual ~application() = default;

    void main();

private:
    bool on_frame_begin(const float dt) override;

    void on_keyboard_key_state_changed_event(aeon::input::keyboard_key key, aeon::input::keyboard_key_state key_state,
                                             int modifier) override;

    void on_mouse_button_event(aeon::input::mouse_button button, aeon::input::mouse_button_state button_state) override;

    std::shared_ptr<aeon::scene::orthographic_camera> camera_;

    ship_move_direction move_direction_;
    ship_rotate_direction rotate_direction_;
    float forward_speed_;
};
