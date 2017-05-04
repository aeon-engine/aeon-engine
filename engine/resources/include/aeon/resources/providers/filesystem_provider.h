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

#include <aeon/logger/logger.h>
#include <aeon/resources/providers/resource_provider.h>
#include <aeon/resources/providers/resource_info.h>
#include <aeon/resources/resource_encoding.h>
#include <aeon/resources/exceptions.h>
#include <aeon/io/io_interface.h>
#include <vector>
#include <string>

namespace aeon
{
namespace resources
{

class filesystem_provider : public resource_provider
{
public:
    explicit filesystem_provider(const resource_info &info, std::unique_ptr<io::io_file_interface> &&file_interface);
    virtual ~filesystem_provider();

private:
    void read(std::vector<std::uint8_t> &buffer) override;
    void read(std::vector<std::uint8_t> &buffer, const int size) override;
    void write(std::vector<std::uint8_t> &buffer) override;
    void write(std::vector<std::uint8_t> &buffer, const int size) override;
    void seek_read(io::io_file_interface::seek_direction direction, const int offset) override;
    void seek_write(io::io_file_interface::seek_direction direction, const int offset) override;
    auto get_size() const -> int override;
    auto get_info() const -> resource_info override;

    std::unique_ptr<io::io_file_interface> file_interface_;
    resource_info info_;
};

} // namespace resources
} // namespace aeon
