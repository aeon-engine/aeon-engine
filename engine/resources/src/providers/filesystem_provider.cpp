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

std::size_t filesystem_provider::read(std::uint8_t *data, std::size_t size)
{
    return file_interface_->read(data, size);
}

std::size_t filesystem_provider::write(const std::uint8_t *data, std::size_t size)
{
    return file_interface_->write(data, size);
}

bool filesystem_provider::peek(std::uint8_t &data, std::ptrdiff_t offset)
{
    return file_interface_->peek(data, offset);
}

bool filesystem_provider::seek(std::ptrdiff_t pos, seek_direction direction)
{
    return file_interface_->seek(pos, direction);
}

bool filesystem_provider::seekw(std::ptrdiff_t pos, seek_direction direction)
{
    return file_interface_->seekw(pos, direction);
}

std::size_t filesystem_provider::tell()
{
    return file_interface_->tell();
}

std::size_t filesystem_provider::tellw()
{
    return file_interface_->tellw();
}

bool filesystem_provider::eof() const
{
    return file_interface_->eof();
}

std::size_t filesystem_provider::size() const
{
    return file_interface_->size();
}

void filesystem_provider::flush()
{
    file_interface_->flush();
}

bool filesystem_provider::good() const
{
    return file_interface_->good();
}

auto filesystem_provider::get_info() const -> resource_info
{
    return info_;
}

} // namespace resources
} // namespace aeon
