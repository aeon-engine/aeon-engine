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

#include <assets/asset_manager.h>

namespace aeon
{
namespace assets
{

asset_manager::asset_manager(resources::resource_manager &resource_manager, scene::scene_manager &scene_manager)
    : logger_(common::logger::get_singleton(), "Assets::AssetManager")
    , resource_manager_(resource_manager)
    , scene_manager_(scene_manager)
    , device_(scene_manager.get_device())
{
}

asset_manager::~asset_manager()
{
}

gfx::texture_ptr asset_manager::load_texture(const std::string &path) const
{
    AEON_LOG_DEBUG(logger_) << "Loading texture '" << path << "'." << std::endl;

    resources::image_resource_wrapper_ptr image_resource = resource_manager_.load_image_wrapper(path);
    resources::image_ptr image_resource_data = image_resource->open();
    return device_.get_texture_manager().load(image_resource_data);
}

gfx::shader_ptr asset_manager::load_shader(const std::string &path) const
{
    AEON_LOG_DEBUG(logger_) << "Loading shader '" << path << "'." << std::endl;

    resources::shader_resource_wrapper_ptr shader_resource = resource_manager_.load_shader_wrapper(path);
    resources::shader_ptr shader_resource_data = shader_resource->open();
    return device_.get_shader_manager().load(shader_resource_data);
}

gfx::material_ptr asset_manager::load_material(const std::string &path) const
{
    AEON_LOG_DEBUG(logger_) << "Loading material '" << path << "'." << std::endl;

    resources::material_resource_wrapper_ptr material_resource = resource_manager_.load_material_wrapper(path);
    resources::material_ptr material_resource_data = material_resource->open();
    return device_.get_material_manager().load(material_resource_data);
}

gfx::atlas_ptr asset_manager::load_atlas(const std::string& path) const
{
    AEON_LOG_DEBUG(logger_) << "Loading atlas '" << path << "'." << std::endl;

    resources::atlas_resource_wrapper_ptr atlas_resource = resource_manager_.load_atlas_wrapper(path);
    resources::atlas_ptr atlas_resource_data = atlas_resource->open();
    return device_.get_atlas_manager().load(atlas_resource_data);
}

scene::scene_node_ptr asset_manager::load_mesh(const std::string &path) const
{
    AEON_LOG_DEBUG(logger_) << "Loading mesh '" << path << "'." << std::endl;

    resources::mesh_resource_wrapper_ptr mesh_resource = resource_manager_.load_mesh_wrapper(path);
    resources::mesh_ptr mesh = mesh_resource->open();

    resources::mesh_node &mesh_root_node = mesh->get_root_mesh_node();
    scene::scene_node_ptr scene_node = scene_manager_.create_detached_scene_node();

    __convert_mesh_node_to_scene_node(mesh_root_node, *scene_node);

    return scene_node;
}

gfx::atlas_ptr asset_manager::create_atlas(resources::material_ptr material, glm::vec2 sprite_size) const
{
    gfx::material_ptr gfx_material = device_.get_material_manager().load(material);
    return std::make_shared<gfx::atlas>(gfx_material, sprite_size);
}

gfx::atlas_ptr asset_manager::create_atlas(gfx::material_ptr material, glm::vec2 sprite_size) const
{
    return std::make_shared<gfx::atlas>(material, sprite_size);
}

void asset_manager::__convert_mesh_node_to_scene_node(resources::mesh_node &mesh_node, scene::scene_node &scene_node) const
{
    auto children = mesh_node.get_children();
    for (resources::mesh_node *mesh_node_child : children)
    {
        scene::scene_node_ptr scene_node_child = scene_node.create_child_scene_node();
        __convert_mesh_node_to_scene_node(*mesh_node_child, *scene_node_child);
    }
}

} // namespace assets
} // namespace aeon
