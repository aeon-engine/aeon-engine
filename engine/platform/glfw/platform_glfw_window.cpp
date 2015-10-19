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

#include <platform/glfw/platform_glfw_window.h>

namespace aeon
{
namespace platform
{
namespace glfw
{

platform_window::platform_window(int width, int height, const std::string& title, GLFWmonitor *monitor) :
    platform::platform_window(width, height, title),
    window_(nullptr)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    window_ = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);
}

platform_window::~platform_window()
{
    if (window_)
        glfwDestroyWindow(window_);
}

void platform_window::make_current()
{
    glfwMakeContextCurrent(window_);
}

bool platform_window::on_frame(double /*dt*/)
{
    if (glfwWindowShouldClose(window_))
        return false;

    glfwSwapBuffers(window_);
    return true;
}

} // namespace glfw
} // namespace platform
} // namespace aeon
