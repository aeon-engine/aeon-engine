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
#include <scene/orthographic_camera.h>

class application : public aeon::desktop_application<aeon::scene::basic_scene_manager>
{
public:
    explicit application(int argc, char *argv[]);
    virtual ~application() = default;

    void main();

private:
    aeon::scene::orthographic_camera_ptr camera_;
};
