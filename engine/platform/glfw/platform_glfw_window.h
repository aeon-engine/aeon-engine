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
#include <platform/platform_window.h>
#include <common/logger.h>
#include <GLFW/glfw3.h>
#include <memory>

namespace aeon
{
namespace platform
{
namespace glfw
{

class platform_interface;
class platform_window : public platform::platform_window
{
public:
    explicit platform_window(platform_interface *interface, int width, int height, const std::string &title,
                             GLFWmonitor *monitor);
    ~platform_window() override;

    void make_current() override;

    glm::vec2 get_framebuffer_size() override;

private:
    bool __on_frame_start(float dt) override;

    bool __on_frame_end(float dt) override;

    static void __static_keyboard_key_handler(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void __static_mouse_move_handler(GLFWwindow *window, double x, double y);
    static void __static_mouse_button_handler(GLFWwindow *window, int button, int action, int mods);
    static void __static_mouse_scroll_handler(GLFWwindow *window, double xoffset, double yoffset);

    aeon::logger::logger logger_;

    GLFWwindow *window_;
    platform_interface *interface_;
};

using platform_window_ptr = std::shared_ptr<platform_window>;

} // namespace glfw
} // namespace platform
} // namespace aeon
