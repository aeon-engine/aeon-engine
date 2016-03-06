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

#include <platform/generic/platform_generic_filesystem_interface.h>

namespace aeon
{
namespace platform
{
namespace ios
{

class platform_filesystem_interface : public generic::platform_filesystem_interface
{
public:
    platform_filesystem_interface() = default;
    virtual ~platform_filesystem_interface() = default;

    files list(const std::string &path) override;
    std::string get_executable_path() override;
};

} // namespace ios
} // namespace platform
} // namespace aeon
