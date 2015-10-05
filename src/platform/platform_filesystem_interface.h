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

#include <platform/platform_file_interface.h>
#include <platform/platform_file_open_mode.h>
#include <string>
#include <vector>

namespace aeon
{
namespace platform
{

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
        file_entry(const std::string &name_, file_type type_) :
            name(name_),
            type(type_)
        {}

        std::string name;
        file_type type;
    };

    platform_filesystem_interface();
    virtual ~platform_filesystem_interface();

    virtual platform_file_interface_ptr open_file(const std::string &path, int openmode) = 0;
    virtual bool exists(const std::string &path) = 0;
    virtual std::vector<file_entry> list(const std::string &path) = 0;
};

} // namespace platform
} // namespace aeon
