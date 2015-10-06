/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

#include <platform/generic/platform_generic_filesystem_interface.h>
#include <platform/generic/platform_generic_file_interface.h>
#include <boost/filesystem.hpp>

namespace aeon
{
namespace platform
{
namespace generic
{

platform_filesystem_interface::platform_filesystem_interface()
{
}

platform_filesystem_interface::~platform_filesystem_interface()
{
}

platform::platform_file_interface_ptr platform_filesystem_interface::open_file(const std::string& path, int openmode)
{
    // Note: we can't use make_shared due to private constructor.
    return platform::platform_file_interface_ptr(new platform_file_interface(path, openmode));
}

bool platform_filesystem_interface::exists(const std::string& path)
{
    return boost::filesystem::exists(path);
}

platform_filesystem_interface::files platform_filesystem_interface::list(const std::string& path)
{
    boost::filesystem::path p = path;

    if (!boost::filesystem::is_directory(p))
        throw platform_filesystem_interface_list_exception();

    boost::filesystem::directory_iterator iterator(p);

    platform_filesystem_interface::files files;
    for (auto f : iterator)
    {
        file_type type = file_type::file;

        if (boost::filesystem::is_directory(f))
            type = file_type::directory;

        files.push_back(file_entry(f.path().filename().string(), type));
    }

    return std::move(files);
}

} // namespace generic
} // namespace platform
} // namespace aeon
