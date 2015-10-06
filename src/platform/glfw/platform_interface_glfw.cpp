/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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

#include <platform/glfw/platform_interface_glfw.h>
#include <platform/glfw/platform_glfw_monitor.h>
#include <GLFW/glfw3.h>

namespace aeon
{
namespace platform
{
namespace glfw
{

platform_interface::platform_interface() :
    initialized_(false)
{
}

platform_interface::~platform_interface()
{
    if (initialized_)
        glfwTerminate();

    initialized_ = false;
}

void platform_interface::initialize()
{
    int result = glfwInit();

    if (result == GL_FALSE)
        throw platform_interface_initialize_exception();

    initialized_ = true;
}

void platform_interface::run()
{
    if (!initialized_)
        throw platform_interface_initialize_exception();

    // TODO: Main loop
    while (1)
    {
    }
}

platform_monitors platform_interface::get_monitors()
{
    if (!initialized_)
        throw platform_interface_initialize_exception();

    int count;
    GLFWmonitor** glfw_monitors = glfwGetMonitors(&count);
    GLFWmonitor* glfw_primary_monitor = glfwGetPrimaryMonitor();

    platform_monitors monitors;

    for (int i = 0; i < count; ++i)
    {
        GLFWmonitor *m = glfw_monitors[i];

        int physical_width;
        int physical_height;
        glfwGetMonitorPhysicalSize(m, &physical_width, &physical_height);

        int x;
        int y;
        glfwGetMonitorPos(m, &x, &y);

        bool primary = (glfw_primary_monitor == m);

        const char *name = glfwGetMonitorName(m);

        monitors.emplace_back(std::make_unique<platform_monitor>(
            m, physical_width, physical_height, x, y, primary, name));
    }

    return monitors;
}

} // namespace glfw
} // namespace platform
} // namespace aeon
