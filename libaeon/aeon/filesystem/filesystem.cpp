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

#include <aeon/filesystem.h>
#include <aeon/platform.h>
#include <stdexcept>
#include <stdlib.h>
#include <stdio.h>

#if (defined(AEON_PLATFORM_OS_OSX) || defined(AEON_PLATFORM_OS_LINUX))
#include <unistd.h>
#elif (defined(AEON_PLATFORM_OS_WINDOWS))
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <io.h>
#endif

namespace aeon
{
namespace filesystem
{

bool exists(const std::string &path)
{
#if (defined(AEON_PLATFORM_OS_OSX) || defined(AEON_PLATFORM_OS_LINUX))
    return (access(path.c_str(), F_OK) != -1);
#elif (defined(AEON_PLATFORM_OS_WINDOWS))
    return ((_access(path.c_str(), 0)) != -1);
#else
    throw std::runtime_error("Filesystem is not yet implemented or untested for this platform.");
#endif
}

void delete_file(const std::string &path)
{
#if (defined(AEON_PLATFORM_OS_WINDOWS) || defined(AEON_PLATFORM_OS_OSX) || defined(AEON_PLATFORM_OS_LINUX))
    if (remove(path.c_str()) != 0)
        throw std::runtime_error("delete_file failed.");
#else
    throw std::runtime_error("Filesystem is not yet implemented or untested for this platform.");
#endif
}

void delete_directory(const std::string &path)
{
#if (defined(AEON_PLATFORM_OS_OSX) || defined(AEON_PLATFORM_OS_LINUX))
    if (rmdir(path.c_str()) != 0)
        throw std::runtime_error("delete_directory failed.");
#elif (defined(AEON_PLATFORM_OS_WINDOWS))
    if (RemoveDirectory(path.c_str()) != 0)
        throw std::runtime_error("delete_directory failed.");
#else
    throw std::runtime_error("Filesystem is not yet implemented or untested for this platform.");
#endif
}

std::string generate_temporary_file_path()
{
    char file_name_buff[512];
    char *file_path = tmpnam(file_name_buff);
    return file_path;
}

} // namespace filesystem
} // namespace aeon
