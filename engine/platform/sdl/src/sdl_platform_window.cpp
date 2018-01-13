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

#include <aeon/platform/sdl/sdl_platform_window.h>
#include <aeon/platform/sdl/sdl_platform_manager.h>
#include <aeon/common/logger.h>

namespace aeon
{
namespace platform
{
namespace sdl
{

sdl_window::sdl_window(sdl_platform_manager &platform_manager, const window_settings &settings)
    : window(settings)
    , logger_(common::logger::get_singleton(), "Platform::SDL::Window")
    , window_(nullptr)
    , context_(nullptr)
    , platform_manager_(platform_manager)
    , cursor_mode_(mouse_cursor_mode::normal)
{
    AEON_LOG_DEBUG(logger_) << "Creating OpenGL 3.3 core profile context with forward compatibility." << std::endl;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    if (settings.get_buffer_mode() == buffer_mode::double_buffer)
    {
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    }
    else
    {
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
    }

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window_ = SDL_CreateWindow(settings.get_title().c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               settings.get_width(), settings.get_height(), SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!window_)
    {
        AEON_LOG_ERROR(logger_) << "Window creation failed: " << SDL_GetError() << std::endl;
        throw platform_exception();
    }

    context_ = SDL_GL_CreateContext(window_);

    if (!context_)
    {
        AEON_LOG_ERROR(logger_) << "Context creation failed: " << SDL_GetError() << std::endl;
        throw platform_exception();
    }

    if (SDL_GL_SetSwapInterval(1) < 0)
    {
        AEON_LOG_ERROR(logger_) << "Setting swap interval failed: " << SDL_GetError() << std::endl;
        throw platform_exception();
    }

    platform_manager_.get_device().add_render_target(this);
}

sdl_window::~sdl_window()
{
    platform_manager_.get_device().remove_render_target(this);

    if (context_)
        SDL_GL_DeleteContext(context_);

    if (window_)
        SDL_DestroyWindow(window_);
}

void sdl_window::make_current()
{
    if (SDL_GL_MakeCurrent(window_, context_) < 0)
    {
        AEON_LOG_ERROR(logger_) << "Make current failed: " << SDL_GetError() << std::endl;
        throw platform_exception();
    }
}

auto sdl_window::get_framebuffer_size() const -> glm::vec2
{
    int width, height;
    SDL_GL_GetDrawableSize(window_, &width, &height);
    return glm::vec2(width, height);
}

void sdl_window::set_mouse_cursor_mode(const mouse_cursor_mode mode)
{
    cursor_mode_ = mode;
}

auto sdl_window::get_mouse_cursor_mode() const -> mouse_cursor_mode
{
    return cursor_mode_;
}

void sdl_window::__reset_scissor() const
{
    auto framebuffer_size = get_framebuffer_size();
    auto rect = common::types::rectangle<float>(0.0f, 0.0f, framebuffer_size.x, framebuffer_size.y);
    platform_manager_.get_device().set_scissor(rect);
}

auto sdl_window::__on_frame_start(float /*dt*/) -> bool
{
    make_current();
    return true;
}

auto sdl_window::__on_frame_end(float /*dt*/) -> bool
{
    __reset_scissor();
    SDL_GL_SwapWindow(window_);
    return true;
}

} // namespace sdl
} // namespace platform
} // namespace aeon
