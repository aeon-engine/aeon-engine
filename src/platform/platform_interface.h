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

#include <memory>
#include <platform/platform_monitor.h>
#include <common/exception.h>

namespace aeon
{
namespace platform
{

DEFINE_EXCEPTION_OBJECT(platform_interface_exception, aeon::common::exception,
    "Generic platform interface exception.");

DEFINE_EXCEPTION_OBJECT(platform_interface_initialize_exception, platform_interface_exception,
    "Could not initialize platform.");

class platform_filesystem_interface;
class platform_window;

class platform_interface
{
public:
    platform_interface() = default;
    virtual ~platform_interface() = default;

    /*!
     * Initialize the engine. This will set up all platform related things like window,
     * contexts, etc. based on your platform.
     */
    virtual void initialize() = 0;

    /*!
     * Enter the engine's main loop. You must first call initialize before calling run.
     */
    virtual void run() = 0;

    /*!
     * Get a list of all monitors connected to this system.
     */
    virtual platform_monitors get_monitors() = 0;

    /*!
     * Get the subsystem for filesystem interaction for this platform.
     */
    std::shared_ptr<platform_filesystem_interface> get_filesystem_interface()
    {
        return filesystem_interface_;
    }

    /*!
     * Get the subsystem for window interaction for this platform.
     */
    std::shared_ptr<platform_window> get_window()
    {
        return window_;
    }

protected:
    std::shared_ptr<platform_filesystem_interface> filesystem_interface_;
    std::shared_ptr<platform_window> window_;
};

} // namespace platform
} // namespace aeon
