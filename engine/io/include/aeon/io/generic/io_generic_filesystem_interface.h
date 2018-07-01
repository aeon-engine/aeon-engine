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

#include <aeon/logger/logger.h>
#include <aeon/io/io_file_interface.h>
#include <aeon/io/io_filesystem_interface.h>
#include <aeon/io/io_file_open_mode.h>
#include <aeon/common/logger.h>
#include <string>
#include <vector>

namespace aeon
{
namespace io
{
namespace generic
{

class io_generic_filesystem_interface : public io::io_filesystem_interface
{
public:
    io_generic_filesystem_interface();
    virtual ~io_generic_filesystem_interface() = default;

    auto open_file(const std::filesystem::path &path, const common::flags<file_open_mode> openmode) const
        -> std::unique_ptr<io_file_interface> override;
    auto exists(const std::filesystem::path &path) const -> bool override;
    auto list(const std::filesystem::path &path) const -> std::vector<file_entry> override;

private:
    logger::logger logger_;
};

} // namespace generic
} // namespace io
} // namespace aeon
