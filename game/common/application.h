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

#include <gfx/gfx_frame_listener.h>
#include <platform/glfw/platform_glfw_interface.h>
#include <resources/resource_manager.h>
#include <resources/providers/filesystem_provider.h>
#include <resources/wrappers/image_resource_wrapper.h>
#include <resources/image.h>
#include <gfx/gl/gfx_gl_device.h>
#include <scene/scene_managers/basic/basic_scene_manager.h>
#include <scene/orthographic_camera.h>
#include <scene/animated_sprite.h>

namespace aeon
{

enum move_direction : int
{
    move_south = 0,
    move_west  = 1,
    move_east  = 2,
    move_north = 3
};

class application : public gfx::frame_listener
{
public:
    application();
    ~application();

    void main(int argc, char *argv[]);

private:
    bool on_frame(float dt) override;

    platform::glfw::platform_interface platform_;
    gfx::gl::device device_;
    platform::platform_window_ptr window_;

    resources::resource_manager resource_manager_;
    scene::basic_scene_manager scene_manager_;
    scene::orthographic_camera_ptr camera_;

    scene::scene_node_ptr ship2_pivot_node_;
    scene::scene_node_ptr ship3_pivot_node_;

    scene::animated_sprite_ptr animated_sprite_;

    float turn_timer_;
    int direction_;
};

} // namespace aeon
