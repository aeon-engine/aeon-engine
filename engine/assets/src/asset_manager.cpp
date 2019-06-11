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

#include <aeon/assets/asset_manager.h>
#include <aeon/resources/image.h>
#include <aeon/resources/shader.h>
#include <aeon/resources/material.h>
#include <aeon/resources/atlas.h>
#include <aeon/resources/mesh.h>
#include <aeon/resources/scene.h>
#include <aeon/scene/components/mesh.h>
#include <aeon/scene/components/perspective_camera.h>
#include <build_config.h>

namespace aeon::assets
{

asset_manager::asset_manager(codecs::codec_manager &codec_manager, resources::resource_manager &resource_manager,
                             scene::scene_manager &scene_manager)
    : logger_(common::logger::get_singleton(), "Assets::AssetManager")
    , codec_manager_(codec_manager)
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

    auto texture = load_texture(load_image(path));
    texture_cache_.add_cached_object(path, texture);
    return texture;
}

auto asset_manager::load_texture(std::shared_ptr<resources::image> image) const -> std::shared_ptr<gfx::texture>
{
    AEON_LOG_DEBUG(logger_) << "Creating texture from image data." << std::endl;
    auto texture = device_.get_texture_manager().create(image->get_data());
    return texture;
}

auto asset_manager::load_shader(const std::string &path) -> std::shared_ptr<gfx::shader>
{
    AEON_LOG_DEBUG(logger_) << "Loading shader '" << path << "'." << std::endl;

    auto result = shader_cache_.get_cached_object(path);

    if (result)
        return result;

    auto collection_provider = resource_manager_.load(path);
    auto encoding = collection_provider->get_info().get_encoding();
    auto codec = codec_manager_.create_basic<resources::shader>(encoding);
    auto resource = codec->decode(collection_provider);

    auto shader = device_.get_shader_manager().create(resource->get_data());
    shader_cache_.add_cached_object(path, shader);
    return shader;
}

auto asset_manager::load_material(const std::string &path) -> std::shared_ptr<gfx::material>
{
    AEON_LOG_DEBUG(logger_) << "Loading material '" << path << "'." << std::endl;

    auto result = material_cache_.get_cached_object(path);

    if (result)
        return result;

    auto collection_provider = resource_manager_.load(path);
    auto encoding = collection_provider->get_info().get_encoding();
    auto codec = codec_manager_.create_basic<resources::material>(encoding);
    auto resource = codec->decode(collection_provider);

    auto &material_data = resource->get_material_data();

#ifdef AEON_GFX_GL
    auto shader = load_shader(material_data.shaders.at("gl3"));
#else // AEON_GFX_GL
#ifdef AEON_GFX_GLES2
    auto shader = load_shader(material_data.shaders.at("gles2"));
#else
    static_assert(false, "Invalid or unsupported gfx subsystem selected.");
#endif // AEON_GFX_GLES2
#endif // AEON_GFX_GL

    auto sampler_map = std::map<std::string, std::shared_ptr<gfx::texture>>();

    for (auto &sampler : material_data.samplers)
    {
        if (sampler->name)
            sampler_map[sampler->name.value_or("")] = load_texture(sampler->path.value_or(""));
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

    auto collection_provider = resource_manager_.load(path);
    auto encoding = collection_provider->get_info().get_encoding();
    auto codec = codec_manager_.create_basic<resources::atlas>(encoding);
    auto resource = codec->decode(collection_provider);

    auto material = load_material(resource->get_material_path());

    auto atlas = device_.get_atlas_manager().create(material, resource->get_data());
    atlas_cache_.add_cached_object(path, atlas);
    return atlas;
}

auto asset_manager::load_mesh(const std::string &path) -> std::shared_ptr<scene::scene_node>
{
    AEON_LOG_DEBUG(logger_) << "Loading mesh '" << path << "'." << std::endl;

    auto collection_provider = resource_manager_.load(path);
    auto encoding = collection_provider->get_info().get_encoding();
    auto codec = codec_manager_.create_basic<resources::mesh>(encoding);
    auto resource = codec->decode(collection_provider);

    auto &mesh_root_node = resource->get_root_mesh_node();
    auto scene_node = scene_manager_.create_detached_scene_node(mesh_root_node.get_name());

    __convert_mesh_node_to_scene_node(mesh_root_node, *scene_node);

    return scene_node;
}

auto asset_manager::load_scene(const std::string &path) -> std::shared_ptr<scene::scene_node>
{
    AEON_LOG_DEBUG(logger_) << "Loading scene '" << path << "'." << std::endl;

    auto collection_provider = resource_manager_.load(path);
    auto encoding = collection_provider->get_info().get_encoding();
    auto codec = codec_manager_.create_basic<resources::scene>(encoding);
    auto resource = codec->decode(collection_provider);

    auto &scene_data = resource->get_scene_data();
    auto scene_node = scene_manager_.create_detached_scene_node(scene_data.root->name.value_or(""));

    __convert_scene_data_to_scene_node(*scene_data.root, *scene_node);

    return scene_node;
}

auto asset_manager::create_atlas(const std::shared_ptr<gfx::material> &material, math::vector2<float> sprite_size) const
    -> std::shared_ptr<gfx::atlas>
{
    return std::make_shared<gfx::atlas>(material, sprite_size);
}

auto asset_manager::load_image(const std::string &path) const -> std::shared_ptr<resources::image>
{
    AEON_LOG_DEBUG(logger_) << "Loading image '" << path << "'." << std::endl;

    auto collection_provider = resource_manager_.load(path);
    auto encoding = collection_provider->get_info().get_encoding();
    auto codec = codec_manager_.create_basic<resources::image>(encoding);
    return codec->decode(collection_provider);
}

void asset_manager::__convert_mesh_node_to_scene_node(resources::mesh_node &mesh_node, scene::scene_node &scene_node)
{
    auto submeshes = mesh_node.get_submeshes();

    for (auto submesh : submeshes)
    {
        auto mesh = std::make_shared<scene::mesh>(scene_manager_, load_material(submesh->get_material()),
                                                  submesh->get_vertex_data(), submesh->get_index_data());

        scene_node.attach_component(mesh);
    }

    auto children = mesh_node.get_children();
    for (auto mesh_node_child : children)
    {
        auto scene_node_child = scene_node.create_child_scene_node(mesh_node_child->get_name());
        scene_node_child->set_matrix(mesh_node_child->get_matrix());
        __convert_mesh_node_to_scene_node(*mesh_node_child, *scene_node_child);
    }
}

void asset_manager::__convert_scene_data_to_scene_node(serialization::scene_node &scene_data,
                                                       scene::scene_node &scene_node)
{
    auto &scene_subnodes = scene_data.children;
    for (auto &scene_subnode : scene_subnodes)
    {
        auto subnode = scene_node.create_child_scene_node(scene_subnode->name.value_or(""));
        __convert_scene_data_to_scene_node(*scene_subnode, *subnode);
    }

    scene_node.set_position(scene_data.position.value_or(math::vector3<float>()));
    scene_node.set_rotation(scene_data.rotation.value_or(math::quaternion::indentity()));
    scene_node.set_scale(scene_data.scale.value_or(math::vector3<float>()));

    auto &components = scene_data.objects;
    for (auto &component : components)
    {
        if (component->get_typename() == "mesh")
        {
            auto mesh_object = static_cast<serialization::mesh *>(component.get());
            scene_node.attach_child(load_mesh(mesh_object->path.value_or("")));
        }
        else if (component->get_typename() == "perspective_camera")
        {
            auto perspective_cam_object = static_cast<serialization::perspective_camera *>(component.get());

            if (perspective_cam_object->fov)
            {
                auto camera = std::make_shared<aeon::scene::perspective_camera>(
                    scene_manager_, perspective_cam_object->fov.value_or(0), perspective_cam_object->width.value_or(0),
                    perspective_cam_object->height.value_or(0), perspective_cam_object->near_value.value_or(0),
                    perspective_cam_object->far_value.value_or(0), perspective_cam_object->name.value_or(""));
                scene_node.attach_component(camera);
            }
            else
            {
                auto camera = std::make_shared<aeon::scene::perspective_camera>(
                    scene_manager_, perspective_cam_object->fov_y.value_or(0),
                    perspective_cam_object->aspect_ratio.value_or(0), perspective_cam_object->near_value.value_or(0),
                    perspective_cam_object->far_value.value_or(0), perspective_cam_object->name.value_or(""));
                scene_node.attach_component(camera);
            }
        }
    }
}
} // namespace aeon::assets
