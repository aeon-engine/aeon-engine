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

#include <platform/platform_monitor.h>
#include <platform/platform_window.h>
#include <platform/platform_filesystem_interface.h>
#include <platform/platform_input_handler.h>
#include <common/exception.h>
#include <memory>
#include <functional>

namespace aeon
{

class application_settings;

namespace gfx
{
class device;
} // namespace gfx

namespace platform
{

DEFINE_EXCEPTION_OBJECT(platform_interface_exception, aeon::common::exception, "Generic platform interface exception.");

DEFINE_EXCEPTION_OBJECT(platform_interface_initialize_exception, platform_interface_exception,
                        "Could not initialize platform.");

class platform_interface
{
public:
    explicit platform_interface(gfx::device &device, platform_filesystem_interface_ptr filesystem_interface)
        : device_(device)
        , filesystem_interface_(std::move(filesystem_interface))
    {
    }

    virtual ~platform_interface() = default;

    /*!
     * Initialize the engine. This will set up all platform related things like window,
     * contexts, etc. based on your platform.
     */
    virtual void initialize(const application_settings &settings) = 0;

    /*!
     * Enter the engine's main loop. You must first call initialize before calling run.
     * This function will not return until stop() is called.
     */
    virtual int run(int argc, char *argv[], const application_settings &settings, std::function<void()> callback) = 0;

    /*!
     * Stop the mainloop. Has no effect if run hasn't been called.
     */
    virtual void stop() = 0;

    /*!
     * Get a list of all monitors connected to this system.
     */
    virtual platform_monitors get_monitors() = 0;

    /*!
     * Create a window. A window can be created on a specific monitor. When no monitor is
     * given, the window appears on the main monitor.
     */
    virtual platform_window_ptr create_window(int width, int height, const std::string &name,
                                              platform_monitor_ptr monitor = nullptr) = 0;

    /*!
     * Get the default created window.
     */
    virtual platform_window_ptr get_default_window() = 0;

    /*!
     * Get the subsystem for filesystem interaction for this platform.
     */
    platform_filesystem_interface *get_filesystem_interface() const
    {
        return filesystem_interface_.get();
    }

    /*!
     * Get the input handler for this platform.
     */
    platform_input_handler *get_input_handler()
    {
        return &input_handler_;
    }

protected:
    gfx::device &device_;
    platform_filesystem_interface_ptr filesystem_interface_;
    platform_input_handler input_handler_;
};

} // namespace platform
} // namespace aeon
