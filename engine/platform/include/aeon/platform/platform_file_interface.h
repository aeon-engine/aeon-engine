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

#include <aeon/platform/platform_file_open_mode.h>
#include <aeon/platform/platform_exception.h>
#include <memory>
#include <string>
#include <cstdint>
#include <vector>

namespace aeon
{
namespace platform
{

DEFINE_EXCEPTION_OBJECT(platform_file_exception, platform_exception, "File I/O error.");
DEFINE_EXCEPTION_OBJECT(platform_file_open_exception, platform_file_exception, "Error while opening file.");
DEFINE_EXCEPTION_OBJECT(platform_file_read_exception, platform_file_exception, "Error while reading file.");
DEFINE_EXCEPTION_OBJECT(platform_file_write_exception, platform_file_exception, "Error while writing to file.");

class platform_file_interface
{
    friend class platform_filesystem_interface;

public:
    enum class seek_direction
    {
        begin,
        current,
        end,
    };

    virtual ~platform_file_interface() = default;

    virtual void read(std::vector<std::uint8_t> &buffer) = 0;
    virtual void read(std::vector<std::uint8_t> &buffer, const int size) = 0;

    virtual void write(std::vector<std::uint8_t> &buffer) = 0;
    virtual void write(std::vector<std::uint8_t> &buffer, const int size) = 0;

    virtual void seek_read(seek_direction direction, const int offset) = 0;
    virtual void seek_write(seek_direction direction, const int offset) = 0;

    virtual auto get_size() const -> int = 0;

    const auto &get_path() const
    {
        return path_;
    }

    auto get_open_mode() const
    {
        return openmode_;
    }

protected:
    explicit platform_file_interface(const std::string &path, const int openmode)
        : openmode_(openmode)
        , path_(path)
    {
    }

private:
    int openmode_;
    std::string path_;
};

} // namespace platform
} // namespace aeon
