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
#include <scene/animated_sprite.h>

enum move_direction : int
{
    move_south = 0,
    move_west = 1,
    move_east = 2,
    move_north = 3
};

class application : public aeon::gfx::frame_listener, public aeon::desktop_application<aeon::scene::basic_scene_manager>
{
public:
    explicit application(int argc, char *argv[]);
    virtual ~application() = default;

    void main();

private:
    bool on_frame(float dt) override;

    aeon::scene::orthographic_camera_ptr camera_;

    aeon::scene::animated_sprite_ptr animated_sprite_;

    float turn_timer_;
    int direction_;
};
