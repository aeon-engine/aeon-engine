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

bool platform_window::pre_frame()
{
    glfwMakeContextCurrent(window_);
    return !glfwWindowShouldClose(window_);
}

bool platform_window::frame(double /*dt*/)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    float ratio;
    int width, height;
    glfwGetFramebufferSize(window_, &width, &height);
    ratio = width / (float)height;
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

    glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
    glEnd();

    glFlush();
    glfwSwapBuffers(window_);

    return !glfwWindowShouldClose(window_);
}

bool platform_window::post_frame()
{
    return !glfwWindowShouldClose(window_);
}

} // namespace glfw
} // namespace platform
} // namespace aeon
