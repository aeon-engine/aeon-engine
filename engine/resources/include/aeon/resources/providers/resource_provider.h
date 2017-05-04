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

#include <aeon/resources/providers/resource_info.h>
#include <aeon/io/io_file_interface.h>
#include <aeon/resources/exceptions.h>
#include <aeon/common/noncopyable.h>
#include <vector>
#include <cstdint>

namespace aeon
{
namespace resources
{

DEFINE_EXCEPTION_OBJECT(resource_provider_exception, resource_exception, "Generic Resource Provider exception.");

class resource_provider : public common::noncopyable
{
public:
    resource_provider() = default;
    virtual ~resource_provider() = default;

    virtual void read(std::vector<std::uint8_t> &buffer) = 0;
    virtual void read(std::vector<std::uint8_t> &buffer, const int size) = 0;

    virtual void write(std::vector<std::uint8_t> &buffer) = 0;
    virtual void write(std::vector<std::uint8_t> &buffer, const int size) = 0;

    virtual void seek_read(io::io_file_interface::seek_direction direction, const int offset) = 0;
    virtual void seek_write(io::io_file_interface::seek_direction direction, const int offset) = 0;

    virtual auto get_size() const -> int = 0;

    virtual auto get_info() const -> resource_info = 0;
};

} // namespace resources
} // namespace aeon
