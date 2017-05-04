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

#include <aeon/resources/providers/filesystem_provider.h>

namespace aeon
{
namespace resources
{
filesystem_provider::filesystem_provider(const resource_info &info,
                                         std::unique_ptr<io::io_file_interface> &&file_interface)
    : file_interface_(std::move(file_interface))
    , info_(info)
{
}

filesystem_provider::~filesystem_provider() = default;

void filesystem_provider::read(std::vector<std::uint8_t> &buffer)
{
    file_interface_->read(buffer);
}

void filesystem_provider::read(std::vector<std::uint8_t> &buffer, const int size)
{
    file_interface_->read(buffer, size);
}

void filesystem_provider::write(std::vector<std::uint8_t> &buffer)
{
    file_interface_->write(buffer);
}

void filesystem_provider::write(std::vector<std::uint8_t> &buffer, const int size)
{
    file_interface_->write(buffer, size);
}

void filesystem_provider::seek_read(io::io_file_interface::seek_direction direction, const int offset)
{
    file_interface_->seek_read(direction, offset);
}

void filesystem_provider::seek_write(io::io_file_interface::seek_direction direction, const int offset)
{
    file_interface_->seek_write(direction, offset);
}

auto filesystem_provider::get_size() const -> int
{
    return file_interface_->get_size();
}

auto filesystem_provider::get_info() const -> resource_info
{
    return info_;
}

} // namespace resources
} // namespace aeon
