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

#include <application/aeon_application.h>
#include <gfx/gfx_frame_listener.h>
#include <resources/wrappers/image_resource_wrapper.h>
#include <scene/scene_managers/basic/basic_scene_manager.h>
#include <scene/orthographic_camera.h>

class application : public aeon::gfx::frame_listener, public aeon::aeon_application<aeon::scene::basic_scene_manager>
{
public:
    application();
    virtual ~application() = default;

    void main(int argc, char *argv[]);

private:
    bool on_frame(float dt) override;

    aeon::scene::orthographic_camera_ptr camera_;

    aeon::scene::scene_node_ptr ship2_pivot_node_;
    aeon::scene::scene_node_ptr ship3_pivot_node_;
};
