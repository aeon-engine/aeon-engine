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

#include <platform/null/platform_null_interface.h>
#include <platform/null/platform_null_monitor.h>
#include <platform/null/platform_null_window.h>
#include <platform/generic/platform_generic_filesystem_interface.h>

namespace aeon
{
namespace platform
{
namespace null
{

platform_interface::platform_interface(int argc, char *argv[])
    : platform::platform_interface(argc, argv, std::make_unique<generic::platform_filesystem_interface>())
    , logger_(common::logger::get_singleton(), "Platform::Null")
    , initialized_(false)
    , running_(false)
{
}

platform_interface::~platform_interface()
{
    initialized_ = false;
}

void platform_interface::initialize()
{
    AEON_LOG_MESSAGE(logger_) << "Initializing Null interface." << std::endl;
    initialized_ = true;
}

void platform_interface::run()
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error starting message loop. Platform not initialized." << std::endl;
        throw platform_interface_initialize_exception();
    }

    AEON_LOG_DEBUG(logger_) << "Starting message loop." << std::endl;

    running_ = true;

    while (running_)
    {
        double delta_time = 0.1; // This should be handled better.

        for (gfx::render_target_ptr render_target : render_targets_)
        {
            if (!render_target->handle_frame(static_cast<float>(delta_time)))
            {
                running_ = false;
                break;
            }
        }
    }

    AEON_LOG_DEBUG(logger_) << "Message loop stopped." << std::endl;
}

void platform_interface::stop()
{
    AEON_LOG_DEBUG(logger_) << "Stopping message loop." << std::endl;
    running_ = false;
}

platform_monitors platform_interface::get_monitors()
{
    platform_monitors monitors;
    // TODO: handle this better.
    monitors.emplace_back(std::make_unique<null::platform_monitor>(1920, 1080, 0, 0, true, "Null Monitor"));
    return monitors;
}

platform::platform_window_ptr platform_interface::create_window(const platform_window_settings &settings,
                                                                platform_monitor_ptr monitor)
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error creating window. Platform not initialized." << std::endl;
        throw platform_interface_initialize_exception();
    }

    AEON_LOG_DEBUG(logger_) << "Creating window: " << settings.get_width() << "x" << settings.get_height() << " '"
                            << settings.get_title() << "'." << std::endl;

    platform_window_ptr window = std::make_shared<null::platform_window>(this, settings);

    render_targets_.push_back(window);

    return window;
}

} // namespace null
} // namespace platform
} // namespace aeon
