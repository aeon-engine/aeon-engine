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
#include <aeon/resources/wrappers/image_resource_wrapper.h>
#include <aeon/scene/basic_scene_manager/basic_scene_manager.h>
#include <aeon/scene/perspective_camera.h>

class application : public aeon::gfx::frame_listener, public aeon::desktop_application<aeon::scene::basic_scene_manager>
{
public:
    explicit application();
    virtual ~application() = default;

    void main();

    bool on_frame(float dt) override;

private:
    float timer_;
    aeon::scene::perspective_camera_ptr camera_;
    aeon::scene::scene_node_ptr rotation_node_;
    aeon::scene::scene_node_ptr wave_node_;
};
