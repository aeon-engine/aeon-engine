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

resource_manager::resource_manager(platform::platform_interface &platform, gfx::device &device)
    : platform_(platform)
    , device_(device)
{
}

void resource_manager::mount(resource_provider_ptr provider, const std::string &mountpoint /* = "/"*/)
{
    auto result = mount_points_.find(mountpoint);

    if (result != mount_points_.end())
        throw resource_manager_duplicate_mount_exception();

    mount_points_[mountpoint] = provider;

    provider->manager_ = this;
}

void resource_manager::unmount(const std::string &mountpoint)
{
    auto result = mount_points_.find(mountpoint);

    if (result == mount_points_.end())
        return;

    result->second->manager_ = nullptr;

    mount_points_.erase(result);
}

gfx::texture_ptr resource_manager::load_texture(const std::string &path)
{
    image_resource_wrapper_ptr image_resource = load_image_wrapper(path);
    image_ptr image_resource_data = image_resource->open();
    return device_.get_texture_manager().load(image_resource_data);
}

gfx::shader_ptr resource_manager::load_shader(const std::string &path)
{
    shader_resource_wrapper_ptr shader_resource = load_shader_wrapper(path);
    shader_ptr shader_resource_data = shader_resource->open();
    return device_.get_shader_manager().load(shader_resource_data);
}

gfx::material_ptr resource_manager::load_material(const std::string &path)
{
    material_resource_wrapper_ptr material_resource = load_material_wrapper(path);
    material_ptr material_resource_data = material_resource->open();
    return device_.get_material_manager().load(material_resource_data);
}

image_resource_wrapper_ptr resource_manager::load_image_wrapper(const std::string &path)
{
    std::string real_path;
    resource_provider_ptr best_match_provider = __find_best_match_provider(path, real_path);

    if (!best_match_provider)
        return nullptr;

    return std::make_shared<image_resource_wrapper>(*this, real_path, best_match_provider);
}

material_resource_wrapper_ptr resource_manager::load_material_wrapper(const std::string &path)
{
    std::string real_path;
    resource_provider_ptr best_match_provider = __find_best_match_provider(path, real_path);

    if (!best_match_provider)
        return nullptr;

    return std::make_shared<material_resource_wrapper>(*this, real_path, best_match_provider);
}

shader_resource_wrapper_ptr resource_manager::load_shader_wrapper(const std::string &path)
{
    std::string real_path;
    resource_provider_ptr best_match_provider = __find_best_match_provider(path, real_path);

    if (!best_match_provider)
        return nullptr;

    return std::make_shared<shader_resource_wrapper>(*this, real_path, best_match_provider);
}

resource_provider_ptr resource_manager::__find_best_match_provider(const std::string &path, std::string &provider_path)
{
    // TODO: This needs optimization. Too much looping and string manipulation going on.

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
            if (path.compare(0, p_length, p) == 0)
            {
                best_match_length = p_length;
                best_match_provider = mountpoint.second;
            }
        }
    }

    if (!best_match_provider)
        return nullptr;

    provider_path = path.substr(best_match_length);

    return best_match_provider;
}

} // namespace resources
} // namespace aeon
