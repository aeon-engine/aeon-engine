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
#include <resources/wrappers/image_resource_wrapper.h>
#include <scene/scene_managers/basic/basic_scene_manager.h>
#include <platform/platform_input_listener.h>
#include <scene/perspective_camera.h>

enum class ship_move_direction
{
    none,
    forward,
    reverse
};

class application : public aeon::gfx::frame_listener, public aeon::desktop_application<aeon::scene::basic_scene_manager>, public aeon::platform::platform_input_listener
{
public:
    explicit application(int argc, char *argv[]);
    virtual ~application() = default;

    void main();

    bool on_frame(float dt) override;

private:
    void on_keyboard_event(aeon::platform::platform_window *window, aeon::platform::keyboard_key key,
        aeon::platform::keyboard_key_state key_state, int modifier) override;

    void on_mouse_move_event(aeon::platform::platform_window *window, float x, float y) override;

    float timer_;
    aeon::scene::perspective_camera_ptr camera_;
    aeon::scene::scene_node_ptr camera_node_position_;
    aeon::scene::scene_node_ptr camera_node_x_;
    aeon::scene::scene_node_ptr camera_node_y_;

    aeon::scene::scene_node_ptr rotation_node_;
    aeon::scene::scene_node_ptr wave_node_;

    float previous_mouse_x_;
    float previous_mouse_y_;

    ship_move_direction move_direction_;
    float forward_speed_;
};
