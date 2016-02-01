/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
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

#include <platform/generic/platform_generic_filesystem_interface.h>
#include <platform/generic/platform_generic_file_interface.h>
#include <aeon/filesystem.h>

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

platform::platform_file_interface_ptr platform_filesystem_interface::open_file(const std::string &path, int openmode)
{
    // Note: we can't use make_shared due to private constructor.
    return std::make_shared<platform::generic::platform_file_interface>(path, openmode);
}

bool platform_filesystem_interface::exists(const std::string &path)
{
    return filesystem::exists(path);
}

platform_filesystem_interface::files platform_filesystem_interface::list(const std::string & /*path*/)
{
    throw std::runtime_error("Not yet implemented.");
}

} // namespace generic
} // namespace platform
} // namespace aeon
