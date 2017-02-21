/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
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
        explicit file_entry(const std::string &name_, const file_type type_)
            : name(name_)
            , type(type_)
        {
        }

        std::string name;
        file_type type;
    };

    platform_filesystem_interface() = default;
    virtual ~platform_filesystem_interface() = default;

    virtual auto open_file(const std::string &path, const int openmode) const
        -> std::shared_ptr<platform_file_interface> = 0;
    virtual auto exists(const std::string &path) const -> bool = 0;
    virtual auto list(const std::string &path) const -> std::vector<file_entry> = 0;
};

} // namespace platform
} // namespace aeon
