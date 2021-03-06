/*
 * Copyright (c) 2012-2018 Robin Degen
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

#include <aeon/streams/idynamic_stream.h>
#include <aeon/common/exception.h>
#include <filesystem>
#include <memory>
#include <vector>

namespace aeon::io
{

DEFINE_EXCEPTION_OBJECT(io_filesystem_interface_exception, aeon::common::exception,
                        "Generic IO filesystem interface exception.");

DEFINE_EXCEPTION_OBJECT(io_filesystem_interface_list_exception, io_filesystem_interface_exception,
                        "IO filesystem interface list exception. Given path is not a directory.");

enum class file_type
{
    file,
    directory
};

enum class file_open_mode
{
    read,
    write,
    truncate
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

class io_filesystem_interface
{
public:
    io_filesystem_interface() = default;
    virtual ~io_filesystem_interface() = default;

    virtual auto open_file(const std::filesystem::path &path, const file_open_mode openmode) const
        -> std::unique_ptr<streams::idynamic_stream> = 0;
    virtual auto exists(const std::filesystem::path &path) const -> bool = 0;
    virtual auto list(const std::filesystem::path &path) const -> std::vector<file_entry> = 0;
};

} // namespace aeon::io
