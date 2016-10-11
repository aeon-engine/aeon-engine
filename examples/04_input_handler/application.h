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
#include <gfx/gfx_frame_listener.h>
#include <resources/wrappers/image_resource_wrapper.h>
#include <scene/scene_managers/basic/basic_scene_manager.h>
#include <scene/orthographic_camera.h>
#include <aeon/platform/platform_input_listener.h>

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
                    public aeon::platform::platform_input_listener
{
public:
    explicit application();
    virtual ~application() = default;

    void main();

private:
    bool on_frame(float dt) override;

    void on_keyboard_event(aeon::platform::keyboard_key key, aeon::platform::keyboard_key_state key_state, int modifier) override;

    void on_mouse_button_event(aeon::platform::mouse_button button, aeon::platform::mouse_button_state button_state) override;

    aeon::scene::orthographic_camera_ptr camera_;

    ship_move_direction move_direction_;
    ship_rotate_direction rotate_direction_;
    float forward_speed_;
};
