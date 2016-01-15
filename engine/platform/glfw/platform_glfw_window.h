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
#include <platform/platform_window.h>
#include <GLFW/glfw3.h>
#include <memory>

namespace aeon
{
namespace platform
{
namespace glfw
{

class platform_window : public platform::platform_window
{
    class platform_interface;

public:
    platform_window(int width, int height, const std::string &title, GLFWmonitor *monitor);
    ~platform_window() override;

private:
    void make_current() override;
    bool on_frame(double dt) override;

    GLFWwindow *window_;
};

using platform_window_ptr = std::shared_ptr<platform_window>;

} // namespace glfw
} // namespace platform
} // namespace aeon