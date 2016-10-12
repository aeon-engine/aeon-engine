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

#include <aeon/scene/sprite.h>
#include <aeon/scene/scene_manager.h>

namespace aeon
{
namespace scene
{

sprite::sprite(scene_manager *scene_manager, gfx::atlas_ptr atlas, const data::atlas::region &region, glm::vec2 size,
               int zorder)
    : scene_object(render_layer::overlay, scene_object_type::sprite, scene_manager)
    , has_z_order(zorder)
    , size_(size)
    , atlas_(atlas)
    , region_(region)
    , mesh_(scene_manager->get_device().create_mesh(atlas->get_material()))
{
    __upload_mesh_data();
}

sprite::~sprite()
{
}

void sprite::set_size(glm::vec2 size)
{
    size_ = size;
}

void sprite::set_size(float width, float height)
{
    size_ = glm::vec2(width, height);
}

glm::vec2 sprite::get_size() const
{
    return size_;
}

gfx::atlas_ptr sprite::get_atlas() const
{
    return atlas_;
}

void sprite::set_atlas_region(const data::atlas::region &region)
{
    region_ = region;
}

data::atlas::region sprite::get_atlas_region() const
{
    return region_;
}

void sprite::render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model, float dt)
{
    update(dt);
    mesh_->render(projection, view, model);
}

void sprite::update(float)
{
}

void sprite::__upload_mesh_data() const
{
    __generate_and_upload_vertex_data();
    __generate_and_upload_index_data();
}

void sprite::__generate_and_upload_vertex_data() const
{
    glm::vec2 size_2 = size_ * 0.5f;
    std::vector<data::vertex_data> vertex_data = {
        // Bottom left
        {glm::vec3{-size_2.x, size_2.y, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}, glm::vec3{region_.u1, region_.v2, 0.0f},
         common::types::color{1.0f, 1.0f, 1.0f, 1.0f}},

        // Bottom right
        {glm::vec3{size_2.x, size_2.y, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}, glm::vec3{region_.u2, region_.v2, 0.0f},
         common::types::color{1.0f, 1.0f, 1.0f, 1.0f}},

        // Top left
        {glm::vec3{-size_2.x, -size_2.y, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}, glm::vec3{region_.u1, region_.v1, 0.0f},
         common::types::color{1.0f, 1.0f, 1.0f, 1.0f}},

        // Top right
        {glm::vec3{size_2.x, -size_2.y, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}, glm::vec3{region_.u2, region_.v1, 0.0f},
         common::types::color{1.0f, 1.0f, 1.0f, 1.0f}}};

    mesh_->upload_vertex_buffer(vertex_data, gfx::buffer_usage::dynamic_usage);
}

void sprite::__generate_and_upload_index_data() const
{
    std::vector<std::uint16_t> index_data = {0, 1, 2, 2, 1, 3};
    mesh_->upload_index_buffer(index_data, gfx::buffer_usage::static_usage);
}

} // namespace scene
} // namespace aeon