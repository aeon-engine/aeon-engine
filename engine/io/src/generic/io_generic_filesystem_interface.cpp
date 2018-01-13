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

#include <aeon/io/generic/io_generic_filesystem_interface.h>
#include <aeon/io/generic/io_generic_file_interface.h>
#include <aeon/filesystem/filesystem.h>

namespace aeon
{
namespace io
{
namespace generic
{

io_generic_filesystem_interface::io_generic_filesystem_interface()
    : logger_(common::logger::get_singleton(), "io::Generic::Filesystem")
{
}

auto io_generic_filesystem_interface::open_file(const std::filesystem::path &path, const int openmode) const
    -> std::unique_ptr<io_file_interface>
{
    AEON_LOG_DEBUG(logger_) << "Opening filesystem file: " << path << " (Mode: " << openmode << ")" << std::endl;
    return std::make_unique<io_generic_file_interface>(path, openmode);
}

auto io_generic_filesystem_interface::exists(const std::filesystem::path &path) const -> bool
{
    const bool exists = std::filesystem::exists(path);

    AEON_LOG_DEBUG(logger_) << "Checking if path exists: " << path << " (Result: " << (exists ? "true" : "false") << ")"
                            << std::endl;

    return exists;
}

auto io_generic_filesystem_interface::list(const std::filesystem::path & /*path*/) const -> std::vector<file_entry>
{
    // TODO: Implement filesystem list.
    AEON_LOG_FATAL(logger_) << "Called filesystem list which is not implemented." << std::endl;
    throw std::runtime_error("Not yet implemented.");
}

} // namespace generic
} // namespace io
} // namespace aeon
