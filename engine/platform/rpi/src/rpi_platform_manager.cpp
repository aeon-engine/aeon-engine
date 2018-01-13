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

#include <aeon/platform/rpi/rpi_platform_manager.h>
#include <aeon/platform/rpi/rpi_platform_window.h>
#include <aeon/platform/platform_window_settings.h>

#include <bcm_host.h>

#include <sys/time.h>

namespace aeon
{
namespace platform
{
namespace rpi
{

rpi_platform_manager::rpi_platform_manager(input::input_handler &input_handler, gfx::device &device)
    : platform_manager(input_handler, device)
    , logger_(common::logger::get_singleton(), "Platform::RPI::Manager")
    , initialized_(false)
    , running_(false)
{
    __initialize_rpi();
    initialized_ = true;
}

rpi_platform_manager::~rpi_platform_manager()
{
    // Cleanup ?
}

void rpi_platform_manager::run()
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error starting message loop. Platform not initialized." << std::endl;
        throw platform_exception();
    }

    AEON_LOG_DEBUG(logger_) << "Starting message loop." << std::endl;

    struct timeval t1, t2;
    struct timezone tz;

    gettimeofday(&t1, &tz);

    running_ = true;

    while (running_)
    {
        gettimeofday(&t2, &tz);
        float delta_time = static_cast<float>(t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) * 1e-6);
        t1 = t2;

        if (!get_device().render(delta_time))
            break;
    }

    AEON_LOG_DEBUG(logger_) << "Message loop stopped." << std::endl;
}

void rpi_platform_manager::stop()
{
    AEON_LOG_DEBUG(logger_) << "Stopping Raspberry Pi message loop." << std::endl;
    running_ = false;
}

auto rpi_platform_manager::get_monitors() -> std::vector<monitor *>
{
    // TODO: Implement for rpi
    throw platform_exception();
}

auto rpi_platform_manager::create_window(const window_settings &settings, monitor *monitor) -> std::shared_ptr<window>
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error creating window. Platform not initialized." << std::endl;
        throw platform_exception();
    }

    AEON_LOG_DEBUG(logger_) << "Creating window: " << settings.get_width() << "x" << settings.get_height() << " '"
                            << settings.get_title() << "'." << std::endl;

    auto window = std::make_shared<rpi_window>(*this, settings);

    // Register this window as render target to the gfx device.
    // TODO: ownership? The device should not own this render target.
    get_device().add_render_target(window);

    return window;
}

void rpi_platform_manager::__initialize_rpi() const
{
    AEON_LOG_MESSAGE(logger_) << "Initializing Raspberry Pi." << std::endl;

    bcm_host_init();

    AEON_LOG_DEBUG(logger_) << "Successfully initialized Raspberry Pi." << std::endl;
}

} // namespace rpi
} // namespace platform
} // namespace aeon
