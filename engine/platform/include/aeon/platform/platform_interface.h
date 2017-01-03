/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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
#include <aeon/common/exception.h>
#include <aeon/utility.h>
#include <memory>

namespace aeon
{
namespace platform
{

class platform_interface : utility::noncopyable
{
public:
    explicit platform_interface(std::unique_ptr<platform_filesystem_interface> filesystem_interface)
        : filesystem_interface_(std::move(filesystem_interface))
    {
    }

    virtual ~platform_interface() = default;

    /*!
     * Get the subsystem for filesystem interaction for this platform.
     */
    auto &get_filesystem_interface() const
    {
        platform_filesystem_interface *filesystem_interface = filesystem_interface_.get();
        return *filesystem_interface;
    }

protected:
    std::unique_ptr<platform_filesystem_interface> filesystem_interface_;
};

} // namespace platform
} // namespace aeon
