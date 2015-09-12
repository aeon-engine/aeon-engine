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

#include <resources/resource_manager.h>
#include <resources/resource.h>
#include <resources/resource_type.h>
#include <memory>
#include <string>

namespace aeon
{
namespace resources
{

resource_manager::resource_manager()
{
}

resource_manager::~resource_manager()
{
}

void resource_manager::mount(resource_provider_ptr provider, const std::string &mountpoint /* = "/"*/)
{
    auto result = mount_points_.insert_ex(mountpoint, provider);

    if (result == mount_points_.end())
        throw resource_manager_duplicate_mount_exception();
}

void resource_manager::unmount(const std::string &mountpoint)
{
    mount_points_.erase(mountpoint);
}

resource_ptr resource_manager::load(const std::string &path)
{
    // TODO: This needs optimization. Too much looping and string manipulation going on.

    std::size_t best_match_length = 0;
    resource_provider_ptr best_match_provider = nullptr;

    for (auto &mountpoint : mount_points_)
    {
        std::string p = mountpoint.first;
        std::size_t p_length = p.length();

        if (p_length > best_match_length)
        {
            if (path.compare(0, p_length, p) == 0)
            {
                best_match_length = p_length;
                best_match_provider = mountpoint.second;
            }
        }
    }

    if (!best_match_provider)
        return nullptr;

    std::string real_path = path.substr(best_match_length);

    // Note: std::make_shared doesn't work due to private constructor
    return resource_ptr(new resource(*this, real_path, best_match_provider));
}

} // namespace resources
} // namespace aeon
