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

#include <aeon/io/generic/io_generic_filesystem_interface.h>
#include <aeon/io/generic/io_generic_file_interface.h>
#include <aeon/filesystem.h>
#include <aeon/utility.h>

namespace aeon
{
namespace io
{
namespace generic
{

io_filesystem_interface::io_filesystem_interface()
    : logger_(common::logger::get_singleton(), "io::Generic::Filesystem")
{
}

auto io_filesystem_interface::open_file(const std::string &path, const int openmode) const
    -> std::shared_ptr<io::io_file_interface>
{
    AEON_LOG_DEBUG(logger_) << "Opening filesystem file: " << path << " (Mode: " << openmode << ")" << std::endl;

    // Note: we can't use make_shared due to private constructor.
    return std::make_shared<io::generic::io_file_interface>(path, openmode);
}

auto io_filesystem_interface::exists(const std::string &path) const -> bool
{
    bool exists = filesystem::exists(path);

    AEON_LOG_DEBUG(logger_) << "Checking if path exists: " << path << " (Result: " << (exists ? "true" : "false") << ")"
                            << std::endl;

    return exists;
}

auto io_filesystem_interface::list(const std::string & /*path*/) const -> std::vector<file_entry>
{
    AEON_LOG_FATAL(logger_) << "Called filesystem list which is not implemented." << std::endl;
    throw std::runtime_error("Not yet implemented.");
}

} // namespace generic
} // namespace io
} // namespace aeon
