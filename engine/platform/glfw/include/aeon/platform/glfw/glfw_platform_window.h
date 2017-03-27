/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#include <aeon/platform/platform_window.h>
#include <aeon/io/io_interface.h>
#include <aeon/common/logger.h>
#include <GLFW/glfw3.h>
#include <memory>

namespace aeon
{
namespace platform
{
namespace glfw
{

class glfw_platform_manager;

class glfw_window : public window
{
public:
    explicit glfw_window(glfw_platform_manager &platform_manager, const window_settings &settings,
                         GLFWmonitor *monitor);
    ~glfw_window() override;

    void make_current() override;

    auto get_framebuffer_size() const -> glm::vec2 override;

    void set_mouse_cursor_mode(const mouse_cursor_mode mode) override;

    auto get_mouse_cursor_mode() const -> mouse_cursor_mode override;

    auto get_glfw_window_ptr() const -> GLFWwindow *;

private:
    void __reset_scissor() const;

    bool __on_frame_start(float dt) override;

    bool __on_frame_end(float dt) override;

    static void __static_keyboard_key_handler(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void __static_mouse_move_handler(GLFWwindow *window, double x, double y);
    static void __static_mouse_button_handler(GLFWwindow *window, int button, int action, int mods);
    static void __static_mouse_scroll_handler(GLFWwindow *window, double xoffset, double yoffset);

    auto &get_platform_manager() const
    {
        return platform_manager_;
    }

    aeon::logger::logger logger_;

    GLFWwindow *window_;
    glfw_platform_manager &platform_manager_;
    mouse_cursor_mode cursor_mode_;
};

} // namespace glfw
} // namespace platform
} // namespace aeon
