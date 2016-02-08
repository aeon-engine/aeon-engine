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

#include <application/base_application.h>
#include <resources/providers/filesystem_provider.h>
#include <platform/glfw/platform_glfw_interface.h>
#include <gfx/gl/gfx_gl_device.h>

namespace aeon
{

template<typename scene_manager_t>
class desktop_application : public base_application<platform::glfw::platform_interface, gfx::gl::device, scene_manager_t>
{
public:
    desktop_application(int width, int height, const std::string &window_title)
        : base_application(width, height, window_title)
    {
        // Init resources
        resource_manager_.mount(std::make_shared<resources::filesystem_provider>("."), "/");
    }

    virtual ~desktop_application() = default;

};

} // namespace aeon
