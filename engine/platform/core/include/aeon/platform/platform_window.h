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

#include <aeon/platform/platform_window_settings.h>
#include <aeon/gfx/gfx_render_target.h>
#include <glm/vec2.hpp>
#include <string>
#include <memory>

namespace aeon
{
namespace platform
{

/*!
 * Enum that describes the behaviour of the mouse cursor in relation to the render window.
 */
enum mouse_cursor_mode
{
    normal,  // Normal cursor
    capture, // Capture the cursor (infinite mouse movements)
    hidden,  // Normal cursor, but hidden when moved over the window
};

class window : public gfx::render_target
{
public:
    explicit window(const window_settings &settings);

    virtual ~window() = default;

    auto get_size() const -> glm::vec2;

    void get_size(int &width, int &height) const;

    auto get_title() const -> const std::string &;

    virtual void set_mouse_cursor_mode(const mouse_cursor_mode mode) = 0;
    virtual mouse_cursor_mode get_mouse_cursor_mode() const = 0;

private:
    int width_;
    int height_;
    std::string title_;
};

} // namespace platform
} // namespace aeon
