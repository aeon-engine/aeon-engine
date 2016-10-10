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

#include <aeon/platform/platform_filesystem_interface.h>
#include <aeon/platform/platform_input_handler.h>
#include <aeon/common/exception.h>
#include <memory>

namespace aeon
{
namespace platform
{

class platform_interface
{
public:
    explicit platform_interface(platform_filesystem_interface_ptr filesystem_interface)
        : filesystem_interface_(std::move(filesystem_interface))
    {
    }

    virtual ~platform_interface() = default;

    /*!
     * Get the subsystem for filesystem interaction for this platform.
     */
    platform_filesystem_interface &get_filesystem_interface() const
    {
        platform_filesystem_interface *filesystem_interface = filesystem_interface_.get();
        return *filesystem_interface;
    }

    /*!
     * Get the input handler for this platform.
     */
    platform_input_handler *get_input_handler()
    {
        return &input_handler_;
    }

protected:
    platform_filesystem_interface_ptr filesystem_interface_;
    platform_input_handler input_handler_;
};

} // namespace platform
} // namespace aeon
