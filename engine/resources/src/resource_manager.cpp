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

#include <aeon/resources/resource_manager.h>
#include <aeon/common/literals.h>
#include <memory>
#include <string>

namespace aeon
{
namespace resources
{

resource_manager::resource_manager(io::io_interface &io)
    : logger_(common::logger::get_singleton(), "Resources::ResourceManager")
    , io_(io)
{
    AEON_LOG_TRACE(logger_) << "Created resource manager." << std::endl;
}

resource_manager::~resource_manager()
{
    AEON_LOG_TRACE(logger_) << "Deleted resource manager." << std::endl;
}

void resource_manager::mount(std::unique_ptr<resource_collection_provider> &&provider,
                             const std::string &mountpoint /* = "/"*/)
{
    AEON_LOG_DEBUG(logger_) << "Mounting resource collection provider on '" << mountpoint << "'." << std::endl;

    auto result = mount_points_.find(mountpoint);

    if (result != mount_points_.end())
    {
        AEON_LOG_ERROR(logger_) << "Duplicate mount point." << std::endl;
        throw resource_manager_duplicate_mount_exception();
    }

    mount_points_[mountpoint] = std::move(provider);
}

void resource_manager::unmount(const std::string &mountpoint)
{
    AEON_LOG_DEBUG(logger_) << "Unmounting resource collection provider on '" << mountpoint << "'." << std::endl;

    auto result = mount_points_.find(mountpoint);

    if (result == mount_points_.end())
    {
        AEON_LOG_DEBUG(logger_) << "No resource collection provider was mounted on '" << mountpoint << "'."
                                << std::endl;
        return;
    }

    mount_points_.erase(result);
}

auto resource_manager::__find_best_match_collection_provider(const std::string &path, std::string &provider_path) const
    -> resource_collection_provider *
{
    // TODO: This needs optimization. Too much looping and string manipulation going on.

    AEON_LOG_TRACE(logger_) << "Attempting to best match mountpoint resource collection provider for '" << path << "'."
                            << std::endl;

    if (path.empty())
    {
        AEON_LOG_WARNING(logger_) << "Could not find mountpoint for empty path." << std::endl;
        return nullptr;
    }

    auto actual_path = path;

    if (path[0] != '/')
        actual_path = "/" + path;

    auto best_match_length = 0_size_t;
    resource_collection_provider *best_match_provider = nullptr;

    for (auto &mountpoint : mount_points_)
    {
        auto provider_mount_path = mountpoint.first;
        auto &provider = mountpoint.second;

        auto provider_mount_path_length = provider_mount_path.length();

        // Due to possible mountpoints being inside other mountpoints, the best match provider is the one that
        // has the most in common with the path
        if (provider_mount_path_length > best_match_length)
        {
            if (actual_path.compare(0, provider_mount_path_length, provider_mount_path) == 0)
            {
                best_match_length = provider_mount_path_length;
                best_match_provider = provider.get();
            }
        }
    }

    if (!best_match_provider)
    {
        AEON_LOG_WARNING(logger_) << "Could not find mountpoint for '" << actual_path << "'." << std::endl;
        return nullptr;
    }

    provider_path = actual_path.substr(best_match_length);

    AEON_LOG_TRACE(logger_) << "Found best match mountpoint at '" << provider_path << "'." << std::endl;

    return best_match_provider;
}

} // namespace resources
} // namespace aeon
