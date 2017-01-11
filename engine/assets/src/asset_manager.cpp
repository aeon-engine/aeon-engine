/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#include <aeon/assets/asset_manager.h>
#include <aeon/scene/mesh.h>

namespace aeon
{
namespace assets
{

asset_manager::asset_manager(resources::resource_manager &resource_manager, scene::scene_manager &scene_manager)
    : logger_(common::logger::get_singleton(), "Assets::AssetManager")
    , resource_manager_(resource_manager)
    , scene_manager_(scene_manager)
    , device_(scene_manager.get_device())
    , texture_cache_()
    , shader_cache_()
    , material_cache_()
    , atlas_cache_()
{
}

auto asset_manager::load_texture(const std::string &path) -> std::shared_ptr<gfx::texture>
{
    AEON_LOG_DEBUG(logger_) << "Loading texture '" << path << "'." << std::endl;

    auto result = texture_cache_.get_cached_object(path);

    if (result)
        return result;

    auto image_resource = resource_manager_.load_resource_wrapper<resources::image_resource_wrapper>(path);
    auto image_resource_data = image_resource->open();
    auto texture = device_.get_texture_manager().create(image_resource_data->get_data());
    texture_cache_.add_cached_object(path, texture);
    return texture;
}

auto asset_manager::load_shader(const std::string &path) -> std::shared_ptr<gfx::shader>
{
    AEON_LOG_DEBUG(logger_) << "Loading shader '" << path << "'." << std::endl;

    auto result = shader_cache_.get_cached_object(path);

    if (result)
        return result;

    auto shader_resource = resource_manager_.load_resource_wrapper<resources::shader_resource_wrapper>(path);
    auto shader_resource_data = shader_resource->open();
    auto shader = device_.get_shader_manager().create(shader_resource_data->get_data());
    shader_cache_.add_cached_object(path, shader);
    return shader;
}

auto asset_manager::load_material(const std::string &path) -> std::shared_ptr<gfx::material>
{
    AEON_LOG_DEBUG(logger_) << "Loading material '" << path << "'." << std::endl;

    auto result = material_cache_.get_cached_object(path);

    if (result)
        return result;

    auto material_resource = resource_manager_.load_resource_wrapper<resources::material_resource_wrapper>(path);
    auto material_resource_data = material_resource->open();

    auto &material_data = material_resource_data->get_material_data();

    auto shader = load_shader(material_data.get_shader_path());

    auto samplers = material_data.get_samplers();
    auto sampler_map = std::map<std::string, std::shared_ptr<gfx::texture>>();

    for (auto &sampler : samplers)
    {
        auto &sampler_obj = sampler.second;
        sampler_map[sampler_obj.get_name()] = load_texture(sampler_obj.get_path());
    }

    auto material = device_.get_material_manager().create(shader, sampler_map);
    material_cache_.add_cached_object(path, material);
    return material;
}

auto asset_manager::load_atlas(const std::string &path) -> std::shared_ptr<gfx::atlas>
{
    AEON_LOG_DEBUG(logger_) << "Loading atlas '" << path << "'." << std::endl;

    auto result = atlas_cache_.get_cached_object(path);

    if (result)
        return result;

    auto atlas_resource = resource_manager_.load_resource_wrapper<resources::atlas_resource_wrapper>(path);
    auto atlas_resource_data = atlas_resource->open();
    auto material = load_material(atlas_resource_data->get_material_path());
    auto atlas = device_.get_atlas_manager().create(material, atlas_resource_data->get_data());
    atlas_cache_.add_cached_object(path, atlas);
    return atlas;
}

auto asset_manager::load_mesh(const std::string &path) -> std::shared_ptr<scene::scene_node>
{
    AEON_LOG_DEBUG(logger_) << "Loading mesh '" << path << "'." << std::endl;

    auto mesh_resource = resource_manager_.load_resource_wrapper<resources::mesh_resource_wrapper>(path);
    auto mesh = mesh_resource->open();

    auto &mesh_root_node = mesh->get_root_mesh_node();
    auto scene_node = scene_manager_.create_detached_scene_node(mesh_root_node.get_name());

    __convert_mesh_node_to_scene_node(mesh_root_node, *scene_node);

    return scene_node;
}

auto asset_manager::create_atlas(const std::shared_ptr<gfx::material> &material, glm::vec2 sprite_size) const
    -> std::shared_ptr<gfx::atlas>
{
    return std::make_shared<gfx::atlas>(material, sprite_size);
}

void asset_manager::__convert_mesh_node_to_scene_node(resources::mesh_node &mesh_node, scene::scene_node &scene_node)
{
    auto submeshes = mesh_node.get_submeshes();

    for (auto submesh : submeshes)
    {
        auto mesh = std::make_shared<scene::mesh>(&scene_manager_, load_material(submesh->get_material()),
                                                  submesh->get_vertex_data(), submesh->get_index_data());

        scene_node.attach_scene_object(mesh);
    }

    auto children = mesh_node.get_children();
    for (auto mesh_node_child : children)
    {
        auto scene_node_child = scene_node.create_child_scene_node(mesh_node_child->get_name());
        scene_node_child->set_matrix(mesh_node_child->get_matrix());
        __convert_mesh_node_to_scene_node(*mesh_node_child, *scene_node_child);
    }
}

} // namespace assets
} // namespace aeon
