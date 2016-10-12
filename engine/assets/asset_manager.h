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

#include <aeon/resources/resource_manager.h>
#include <aeon/gfx/gfx_device.h>
#include <aeon/gfx/gfx_shader.h>
#include <aeon/gfx/gfx_texture.h>
#include <aeon/gfx/gfx_material.h>
#include <aeon/gfx/gfx_atlas.h>
#include <aeon/scene/scene_manager.h>
#include <aeon/scene/scene_node.h>
#include <aeon/common/object_cache.h>

namespace aeon
{
namespace assets
{

/*!
 * Asset Manager
 *
 * The asset manager can be used for loading raw data into usable assets like textures. It is introduced as a layer
 * on top of the resource manager to prevent a circular dependency between the resource manager and the serveral
 * subsystems like gfx and audio.
 */
class asset_manager : utility::noncopyable
{
public:
    /*!
     * Constructor
     * \param resource_manager A reference to the resource manager
     * \param scene_manager A reference to the scene manager
     */
    explicit asset_manager(resources::resource_manager &resource_manager, scene::scene_manager &scene_manager);

    /*!
     * Destructor
     */
    virtual ~asset_manager() = default;

    /*!
     * Load a texture from a given image file. Make sure the given file extension has a registed codec in the
     * codec manager.
     * \param path The path to the image file.
     * \return A gfx texture
     */
    gfx::texture_ptr load_texture(const std::string &path);

    /*!
     * Load a shader from a given shader file. Make sure the given file extension has a registed codec in the
     * codec manager.
     * \param path The path to the shader file.
     * \return A gfx shader
     */
    gfx::shader_ptr load_shader(const std::string &path);

    /*!
     * Load a material from a given material file. Make sure the given file extension has a registed codec in the
     * codec manager.
     * \param path The path to the material file.
     * \return A gfx material
     */
    gfx::material_ptr load_material(const std::string &path);

    /*!
     * Load an atlas from a given atlas file. Make sure the given file extension has a registed codec in the
     * codec manager.
     * \param path The path to the atlas file.
     * \return A gfx atlas
     */
    gfx::atlas_ptr load_atlas(const std::string &path);

    /*!
     * Load a mesh from a given mesh file. Make sure the given file extension has a registed codec in the
     * codec manager. This will load the various submeshes into a tree of scene nodes.
     * \param path The path to the mesh file.
     * \return A scene node of the root of the mesh scene.
     */
    scene::scene_node_ptr load_mesh(const std::string &path);

    /*!
     * Generate an atlas based on the given parameters. The atlas will index
     * sprites from the left top to the right bottom.
     * \param material The material to be used for the atlas
     * \param sprite_size The size of an individual sprite on the atlas. They will be auto tiled from left to right,
     *                    top to bottom.
     * \return A gfx atlas
     */
    gfx::atlas_ptr create_atlas(gfx::material_ptr material, glm::vec2 sprite_size) const;

private:
    void __convert_mesh_node_to_scene_node(resources::mesh_node &mesh_node, scene::scene_node &scene_node);

    aeon::logger::logger logger_;
    resources::resource_manager &resource_manager_;
    scene::scene_manager &scene_manager_;
    gfx::device &device_;

    common::object_cache<gfx::texture> texture_cache_;
    common::object_cache<gfx::shader> shader_cache_;
    common::object_cache<gfx::material> material_cache_;
    common::object_cache<gfx::atlas> atlas_cache_;
};

} // namespace assets
} // namespace aeon
