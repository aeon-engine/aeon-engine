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
#include <resources/wrappers/image_resource_wrapper.h>
#include <scene/scene_managers/basic/basic_scene_manager.h>
#include <scene/orthographic_camera.h>

class application : public aeon::aeon_application
{
public:
    application();
    virtual ~application() = default;

    void main(int argc, char *argv[]);

private:
    aeon::scene::basic_scene_manager scene_manager_;
    aeon::scene::orthographic_camera_ptr camera_;
};
