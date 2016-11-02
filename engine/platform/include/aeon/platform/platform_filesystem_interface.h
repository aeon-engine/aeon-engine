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

#include <aeon/platform/platform_file_interface.h>
#include <aeon/platform/platform_file_open_mode.h>
#include <aeon/common/exception.h>
#include <string>
#include <memory>
#include <vector>

namespace aeon
{
namespace platform
{

DEFINE_EXCEPTION_OBJECT(platform_filesystem_interface_exception, aeon::common::exception,
                        "Generic platform filesystem interface exception.");

DEFINE_EXCEPTION_OBJECT(platform_filesystem_interface_list_exception, platform_filesystem_interface_exception,
                        "Platform filesystem interface list exception. Given path is not a directory.");

class platform_filesystem_interface
{
public:
    enum class file_type
    {
        file,
        directory
    };

    class file_entry
    {
    public:
        explicit file_entry(const std::string &name_, file_type type_)
            : name(name_)
            , type(type_)
        {
        }

        std::string name;
        file_type type;
    };

    using files = std::vector<file_entry>;

    platform_filesystem_interface() = default;
    virtual ~platform_filesystem_interface() = default;

    virtual std::shared_ptr<platform_file_interface> open_file(const std::string &path, const int openmode) = 0;
    virtual bool exists(const std::string &path) = 0;
    virtual files list(const std::string &path) = 0;
};

} // namespace platform
} // namespace aeon
