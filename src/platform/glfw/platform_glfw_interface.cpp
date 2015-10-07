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

#include <platform/glfw/platform_glfw_interface.h>
#include <platform/glfw/platform_glfw_monitor.h>
#include <platform/glfw/platform_glfw_window.h>
#include <platform/generic/platform_generic_filesystem_interface.h>
#include <GLFW/glfw3.h>

namespace aeon
{
namespace platform
{
namespace glfw
{

platform_interface::platform_interface() :
    initialized_(false),
    running_(false)
{
    // Note: On GLFW we can use the generic filesystem interface
    filesystem_interface_ = std::make_shared<generic::platform_filesystem_interface>();
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
    running_ = true;
    while (running_)
    {
        glfwPollEvents();
    }
}

void platform_interface::stop()
{
    running_ = false;
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

        monitors.emplace_back(std::make_shared<platform_monitor>(
            m, physical_width, physical_height, x, y, primary, name));
    }

    return monitors;
}

platform_window_ptr platform_interface::create_window(int width, int height, const std::string& name,
    platform_monitor_ptr monitor)
{
    GLFWmonitor *glfw_monitor = nullptr;

    if (monitor)
    {
        std::shared_ptr<platform_monitor> m = std::dynamic_pointer_cast<platform_monitor>(monitor);
        glfw_monitor = m->get_internal_handle();
    }

    std::shared_ptr<platform_window> window = std::make_shared<platform_window>(width, height, name, glfw_monitor);

    return window;
}

} // namespace glfw
} // namespace platform
} // namespace aeon
