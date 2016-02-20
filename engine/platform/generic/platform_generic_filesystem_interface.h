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

#include <platform/platform_file_interface.h>
#include <platform/platform_filesystem_interface.h>
#include <platform/platform_file_open_mode.h>
#include <common/logger.h>
#include <string>
#include <vector>

namespace aeon
{
namespace platform
{
namespace generic
{

class platform_filesystem_interface : public platform::platform_filesystem_interface
{
public:
    platform_filesystem_interface();
    virtual ~platform_filesystem_interface() = default;

    platform::platform_file_interface_ptr open_file(const std::string &path, int openmode) override;
    bool exists(const std::string &path) override;
    files list(const std::string &path) override;

private:
    aeon::logger::logger logger_;
};

} // namespace generic
} // namespace platform
} // namespace aeon
