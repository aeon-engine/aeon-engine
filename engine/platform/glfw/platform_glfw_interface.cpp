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

platform_interface::platform_interface()
    : initialized_(false)
    , running_(false)
    , previous_time_(0.0)
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

    previous_time_ = static_cast<float>(glfwGetTime());

    running_ = true;
    while (running_)
    {
        glfwPollEvents();

        float current_time = static_cast<float>(glfwGetTime());
        float deltaTime = current_time - previous_time_;
        previous_time_ = current_time;

        for (gfx::render_target_ptr render_target : render_targets_)
        {
            if (!render_target->handle_frame(deltaTime))
            {
                running_ = false;
                break;
            }
        }
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
    GLFWmonitor **glfw_monitors = glfwGetMonitors(&count);
    GLFWmonitor *glfw_primary_monitor = glfwGetPrimaryMonitor();

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

        monitors.emplace_back(
            std::make_shared<platform_monitor>(m, physical_width, physical_height, x, y, primary, name));
    }

    return monitors;
}

platform::platform_window_ptr platform_interface::create_window(int width, int height, const std::string &name,
                                                                platform_monitor_ptr monitor)
{
    GLFWmonitor *glfw_monitor = nullptr;

    if (monitor)
    {
        std::shared_ptr<platform_monitor> m = std::dynamic_pointer_cast<platform_monitor>(monitor);
        glfw_monitor = m->get_internal_handle();
    }

    platform_window_ptr window = std::make_shared<glfw::platform_window>(width, height, name, glfw_monitor);

    render_targets_.push_back(window);

    return window;
}

} // namespace glfw
} // namespace platform
} // namespace aeon
