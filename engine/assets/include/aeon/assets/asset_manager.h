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

#pragma once

#include <aeon/codecs/codec_manager.h>
#include <aeon/resources/resource_manager.h>
#include <aeon/resources/mesh_node.h>
#include <aeon/serialization/serialization.h>
#include <aeon/gfx/gfx_device.h>
#include <aeon/gfx/gfx_shader.h>
#include <aeon/gfx/gfx_texture.h>
#include <aeon/gfx/gfx_material.h>
#include <aeon/gfx/gfx_atlas.h>
#include <aeon/scene/scene_manager.h>
#include <aeon/scene/scene_node.h>
#include <aeon/common/object_cache.h>
#include <aeon/logger/logger.h>

namespace aeon::assets
{

/*!
 * Asset Manager
 *
 * The asset manager can be used for loading raw data into usable assets like textures. It is introduced as a layer
 * on top of the resource manager to prevent a circular dependency between the resource manager and the serveral
 * subsystems like gfx and audio.
 */
class asset_manager
{
public:
    /*!
     * Constructor
     * \param resource_manager A reference to the resource manager
     * \param scene_manager A reference to the scene manager
     */
    explicit asset_manager(codecs::codec_manager &codec_manager, resources::resource_manager &resource_manager,
                           scene::scene_manager &scene_manager);

    /*!
     * Destructor
     */
    virtual ~asset_manager() = default;

    asset_manager(const asset_manager &) noexcept = delete;
    auto operator=(const asset_manager &) noexcept -> asset_manager & = delete;

    asset_manager(asset_manager &&) noexcept = default;
    auto operator=(asset_manager &&) noexcept -> asset_manager & = default;

    /*!
     * Load a texture from a given image file. Make sure the given file extension has a registed codec in the
     * codec manager.
     * \param path The path to the image file.
     * \return A gfx texture
     */
    auto load_texture(const std::string &path) -> std::shared_ptr<gfx::texture>;

    /*!
     * Load a texture from given image data.
     * \param image The image data
     * \return A gfx texture
     */
    auto load_texture(std::shared_ptr<resources::image> image) const -> std::shared_ptr<gfx::texture>;

    /*!
     * Load a shader from a given shader file. Make sure the given file extension has a registed codec in the
     * codec manager.
     * \param path The path to the shader file.
     * \return A gfx shader
     */
    auto load_shader(const std::string &path) -> std::shared_ptr<gfx::shader>;

    /*!
     * Load a material from a given material file. Make sure the given file extension has a registed codec in the
     * codec manager.
     * \param path The path to the material file.
     * \return A gfx material
     */
    auto load_material(const std::string &path) -> std::shared_ptr<gfx::material>;

    /*!
     * Load an atlas from a given atlas file. Make sure the given file extension has a registed codec in the
     * codec manager.
     * \param path The path to the atlas file.
     * \return A gfx atlas
     */
    auto load_atlas(const std::string &path) -> std::shared_ptr<gfx::atlas>;

    /*!
     * Load a mesh from a given mesh file. Make sure the given file extension has a registed codec in the
     * codec manager. This will load the various submeshes into a tree of scene nodes.
     * \param path The path to the mesh file.
     * \return A scene node of the root of the mesh scene.
     */
    auto load_mesh(const std::string &path) -> std::shared_ptr<scene::scene_node>;

    /*!
     * Load a scene from a given file. Make sure the given file extension has a registed codec in the
     * codec manager. This will load the whole scene and all it's contents into a tree of scene nodes.
     * \param path The path to the scene file.
     * \return A scene node of the root of the scene.
     */
    auto load_scene(const std::string &path) -> std::shared_ptr<scene::scene_node>;

    /*!
     * Generate an atlas based on the given parameters. The atlas will index
     * sprites from the left top to the right bottom.
     * \param material The material to be used for the atlas
     * \param sprite_size The size of an individual sprite on the atlas. They will be auto tiled from left to right,
     *                    top to bottom.
     * \return A gfx atlas
     */
    auto create_atlas(const std::shared_ptr<gfx::material> &material, const math::vector2<float> sprite_size) const
        -> std::shared_ptr<gfx::atlas>;

    /*!
     * Load an image from a given image file. Make sure the given file extension has a registed codec in the
     * codec manager.
     * \param path The path to the image file.
     * \return A decoded image (raw pixel data)
     */
    auto load_image(const std::string &path) const -> std::shared_ptr<resources::image>;

private:
    void __convert_mesh_node_to_scene_node(resources::mesh_node &mesh_node, scene::scene_node &scene_node);
    void __convert_scene_data_to_scene_node(serialization::scene_node &scene_data, scene::scene_node &scene_node);

    logger::logger logger_;
    codecs::codec_manager &codec_manager_;
    resources::resource_manager &resource_manager_;
    scene::scene_manager &scene_manager_;
    gfx::device &device_;

    common::object_cache<gfx::texture> texture_cache_;
    common::object_cache<gfx::shader> shader_cache_;
    common::object_cache<gfx::material> material_cache_;
    common::object_cache<gfx::atlas> atlas_cache_;
};

} // namespace aeon::assets
