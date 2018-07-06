/*
 * Copyright (c) 2012-2018 Robin Degen
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
#include <aeon/logger/logger.h>
#include <memory>

#include <SDL.h>

namespace aeon
{
namespace platform
{
namespace sdl
{

class sdl_platform_manager;

class sdl_window : public window
{
public:
    explicit sdl_window(sdl_platform_manager &platform_manager, const window_settings &settings);
    ~sdl_window() override;

    void make_current() override;

    auto get_framebuffer_size() const -> math::vector2<float> override;

    void set_mouse_cursor_mode(const mouse_cursor_mode mode) override;

    auto get_mouse_cursor_mode() const -> mouse_cursor_mode override;

private:
    void __reset_scissor() const;

    bool __on_frame_start(float dt) override;

    bool __on_frame_end(float dt) override;

    auto &get_platform_manager() const
    {
        return platform_manager_;
    }

    logger::logger logger_;
    SDL_Window *window_;
    SDL_GLContext context_;
    sdl_platform_manager &platform_manager_;
    mouse_cursor_mode cursor_mode_;
};

} // namespace sdl
} // namespace platform
} // namespace aeon
