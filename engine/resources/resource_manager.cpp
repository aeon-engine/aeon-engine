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

#include <resources/resource_manager.h>
#include <resources/wrappers/resource_wrapper.h>
#include <resources/resource_type.h>
#include <memory>
#include <string>

namespace aeon
{
namespace resources
{

resource_manager::resource_manager(platform::platform_interface &platform)
    : logger_(common::logger::get_singleton(), "Resources::ResourceManager")
    , platform_(platform)
{
    AEON_LOG_TRACE(logger_) << "Created resource manager." << std::endl;
}

resource_manager::~resource_manager()
{
    AEON_LOG_TRACE(logger_) << "Deleted resource manager." << std::endl;
}

void resource_manager::mount(resource_provider_ptr provider, const std::string &mountpoint /* = "/"*/)
{
    AEON_LOG_DEBUG(logger_) << "Mounting resource provider on '" << mountpoint << "'." << std::endl;

    auto result = mount_points_.find(mountpoint);

    if (result != mount_points_.end())
    {
        AEON_LOG_ERROR(logger_) << "Duplicate mount point." << std::endl;
        throw resource_manager_duplicate_mount_exception();
    }

    mount_points_[mountpoint] = provider;

    provider->manager_ = this;
}

void resource_manager::unmount(const std::string &mountpoint)
{
    AEON_LOG_DEBUG(logger_) << "Unmounting resource provider on '" << mountpoint << "'." << std::endl;

    auto result = mount_points_.find(mountpoint);

    if (result == mount_points_.end())
    {
        AEON_LOG_DEBUG(logger_) << "No resource provider was mounted on '" << mountpoint << "'." << std::endl;
        return;
    }

    result->second->manager_ = nullptr;

    mount_points_.erase(result);
}

image_resource_wrapper_ptr resource_manager::load_image_wrapper(const std::string &path)
{
    AEON_LOG_DEBUG(logger_) << "Loading image resource wrapper '" << path << "'." << std::endl;

    std::string real_path;
    resource_provider_ptr best_match_provider = __find_best_match_provider(path, real_path);

    if (!best_match_provider)
        return nullptr;

    return std::make_shared<image_resource_wrapper>(*this, real_path, best_match_provider);
}

material_resource_wrapper_ptr resource_manager::load_material_wrapper(const std::string &path)
{
    AEON_LOG_DEBUG(logger_) << "Loading material resource wrapper '" << path << "'." << std::endl;

    std::string real_path;
    resource_provider_ptr best_match_provider = __find_best_match_provider(path, real_path);

    if (!best_match_provider)
        return nullptr;

    return std::make_shared<material_resource_wrapper>(*this, real_path, best_match_provider);
}

shader_resource_wrapper_ptr resource_manager::load_shader_wrapper(const std::string &path)
{
    AEON_LOG_DEBUG(logger_) << "Loading shader resource wrapper '" << path << "'." << std::endl;

    std::string real_path;
    resource_provider_ptr best_match_provider = __find_best_match_provider(path, real_path);

    if (!best_match_provider)
        return nullptr;

    return std::make_shared<shader_resource_wrapper>(*this, real_path, best_match_provider);
}

atlas_resource_wrapper_ptr resource_manager::load_atlas_wrapper(const std::string &path)
{
    AEON_LOG_DEBUG(logger_) << "Loading atlas resource wrapper '" << path << "'." << std::endl;

    std::string real_path;
    resource_provider_ptr best_match_provider = __find_best_match_provider(path, real_path);

    if (!best_match_provider)
        return nullptr;

    return std::make_shared<atlas_resource_wrapper>(*this, real_path, best_match_provider);
}

mesh_resource_wrapper_ptr resource_manager::load_mesh_wrapper(const std::string &path)
{
    AEON_LOG_DEBUG(logger_) << "Loading mesh resource wrapper '" << path << "'." << std::endl;

    std::string real_path;
    resource_provider_ptr best_match_provider = __find_best_match_provider(path, real_path);

    if (!best_match_provider)
        return nullptr;

    return std::make_shared<mesh_resource_wrapper>(*this, real_path, best_match_provider);
}

resource_provider_ptr resource_manager::__find_best_match_provider(const std::string &path, std::string &provider_path)
{
    // TODO: This needs optimization. Too much looping and string manipulation going on.

    AEON_LOG_TRACE(logger_) << "Attempting to best match mountpoint resource provider for '"
        << path << "'." << std::endl;

    if (path.empty())
    {
        AEON_LOG_WARNING(logger_) << "Could not find mountpoint for empty path." << std::endl;
        return nullptr;
    }

    std::string actual_path = path;

    if (path[0] != '/')
        actual_path = "/" + path;

    std::size_t best_match_length = 0;
    resource_provider_ptr best_match_provider = nullptr;

    for (auto &mountpoint : mount_points_)
    {
        std::string p = mountpoint.first;
        std::size_t p_length = p.length();

        // Due to possible mountpoints being inside other mountpoints, the best match provider is the one that
        // has the most in common with the path
        if (p_length > best_match_length)
        {
            if (actual_path.compare(0, p_length, p) == 0)
            {
                best_match_length = p_length;
                best_match_provider = mountpoint.second;
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
