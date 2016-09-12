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

#pragma once

#include <resources/resource_manager.h>
#include <gfx/gfx_device.h>
#include <gfx/gfx_shader.h>
#include <gfx/gfx_texture.h>
#include <gfx/gfx_material.h>
#include <gfx/gfx_atlas.h>
#include <scene/scene_manager.h>
#include <scene/scene_node.h>

namespace aeon
{
namespace assets
{

class asset_manager
{
public:
    explicit asset_manager(resources::resource_manager &resource_manager, scene::scene_manager &scene_manager);
    ~asset_manager();

    gfx::texture_ptr load_texture(const std::string &path) const;
    gfx::shader_ptr load_shader(const std::string &path) const;
    gfx::material_ptr load_material(const std::string &path) const;
    gfx::atlas_ptr load_atlas(const std::string &path) const;

    scene::scene_node_ptr load_mesh(const std::string &path) const;

    gfx::atlas_ptr create_atlas(resources::material_ptr material, glm::vec2 sprite_size) const;
    gfx::atlas_ptr create_atlas(gfx::material_ptr material, glm::vec2 sprite_size) const;

private:
    void __convert_mesh_node_to_scene_node(resources::mesh_node &mesh_node, scene::scene_node &scene_node) const;

    aeon::logger::logger logger_;
    resources::resource_manager &resource_manager_;
    scene::scene_manager &scene_manager_;
    gfx::device &device_;
};

} // namespace assets
} // namespace aeon
