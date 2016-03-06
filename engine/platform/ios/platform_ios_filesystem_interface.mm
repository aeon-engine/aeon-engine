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

#include <platform/ios/platform_ios_filesystem_interface.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

#import <UIKit/UIKit.h>

namespace aeon
{
namespace platform
{
namespace ios
{

std::string platform_filesystem_interface::get_executable_path()
{
    NSBundle *b = [NSBundle mainBundle];
    NSString *dir = [b resourcePath];

    return [dir fileSystemRepresentation];
}

platform_filesystem_interface::files platform_filesystem_interface::list(const std::string &path)
{
    DIR *dp;
    struct dirent *ep;
    dp = opendir (path.c_str());

    if (dp == nullptr)
        throw std::runtime_error("Could not list directory.");

    platform_filesystem_interface::files file_list;
    while ((ep = readdir(dp)))
    {
        platform_filesystem_interface::file_type type = platform_filesystem_interface::file_type::unknown;

        if (ep->d_type == DT_REG)
            type = platform_filesystem_interface::file_type::file;

        if (ep->d_type == DT_DIR)
            type = platform_filesystem_interface::file_type::directory;

        file_list.push_back(platform_filesystem_interface::file_entry(ep->d_name, type));
    }

    closedir(dp);

    return file_list;
}

} // namespace ios
} // namespace platform
} // namespace aeon
