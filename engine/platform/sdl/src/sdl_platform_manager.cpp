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

#include <aeon/platform/sdl/sdl_platform_manager.h>
#include <aeon/platform/sdl/sdl_platform_window.h>
#include <aeon/platform/platform_window_settings.h>

#include <SDL.h>

namespace aeon
{
namespace platform
{
namespace sdl
{

sdl_platform_manager::sdl_platform_manager(input::input_handler &input_handler, gfx::device &device)
    : platform_manager(input_handler, device)
    , logger_(common::logger::get_singleton(), "Platform::SDL::Manager")
    , initialized_(false)
    , running_(false)
    , previous_time_(0)
{
    __initialize_sdl();
    initialized_ = true;
}

sdl_platform_manager::~sdl_platform_manager()
{
    if (initialized_)
        SDL_Quit();
}

void sdl_platform_manager::run()
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error starting message loop. Platform not initialized." << std::endl;
        throw platform_exception();
    }

    AEON_LOG_DEBUG(logger_) << "Starting message loop." << std::endl;

    previous_time_ = SDL_GetPerformanceCounter();
    auto performance_frequency = static_cast<float>(SDL_GetPerformanceFrequency());

    running_ = true;

    while (running_)
    {
        auto current_time = SDL_GetPerformanceCounter();
        auto delta_time = (current_time - previous_time_) / performance_frequency;
        previous_time_ = current_time;

        if (!__handle_events())
            break;

        if (!get_device().render(delta_time))
            break;
    }

    AEON_LOG_DEBUG(logger_) << "Message loop stopped." << std::endl;
}

void sdl_platform_manager::stop()
{
    AEON_LOG_DEBUG(logger_) << "Stopping GLFW message loop." << std::endl;
    running_ = false;
}

auto sdl_platform_manager::get_monitors() -> std::vector<monitor *>
{
    // TODO: Implement for sdl
    throw platform_exception();
}

auto sdl_platform_manager::create_window(const window_settings &settings, monitor *monitor) -> std::shared_ptr<window>
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error creating window. Platform not initialized." << std::endl;
        throw platform_exception();
    }

    AEON_LOG_DEBUG(logger_) << "Creating window: " << settings.get_width() << "x" << settings.get_height() << " '"
                            << settings.get_title() << "'." << std::endl;

    auto window = std::make_shared<sdl_window>(*this, settings);

    // Register this window as render target to the gfx device.
    // TODO: ownership? The device should not own this render target.
    get_device().add_render_target(window);

    return window;
}

void sdl_platform_manager::__initialize_sdl() const
{
    AEON_LOG_MESSAGE(logger_) << "Initializing SDL." << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        AEON_LOG_FATAL(logger_) << "Could not initialize SDL: " << SDL_GetError() << std::endl;
        throw platform_exception();
    }

    AEON_LOG_DEBUG(logger_) << "Successfully initialized SDL." << std::endl;
}

auto sdl_platform_manager::__handle_events() const -> bool
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            {
                // TODO: Keyboard key numbers don't match those from GLFW, which means input doesn't work properly.
                auto &key_event = event.key;
                auto &keysym = key_event.keysym;
                auto keystate = (event.type == SDL_KEYDOWN) ? input::keyboard_key_state::pressed
                                                            : input::keyboard_key_state::released;
                get_input_handler().handle_keyboard_key_state_changed_event(
                    static_cast<input::keyboard_key>(keysym.sym), keystate, keysym.mod);
            }
            break;

            // TODO: Mouse input.

            case SDL_QUIT:
                return false;

            default:
                break;
        }
    }

    return true;
}

} // namespace sdl
} // namespace platform
} // namespace aeon
