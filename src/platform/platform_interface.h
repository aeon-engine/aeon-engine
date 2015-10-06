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

namespace aeon
{
namespace platform
{

class platform_filesystem_interface;
class platform_window;

class platform_interface
{
public:
    platform_interface();
    virtual ~platform_interface();

    std::shared_ptr<platform_filesystem_interface> get_filesystem_interface()
    {
        return filesystem_interface_;
    }

    std::shared_ptr<platform_window> get_window()
    {
        return window_;
    }

private:
    std::shared_ptr<platform_filesystem_interface> filesystem_interface_;
    std::shared_ptr<platform_window> window_;
};

} // namespace platform
} // namespace aeon
