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

#include <scene/scene_manager.h>
#include <scene/sprite_batch.h>
#include <scene/sprite.h>
#include <algorithm>
#include <GL/glew.h>

namespace aeon
{
namespace scene
{
GLuint vao;
sprite_batch::sprite_batch(scene_manager *scene_manager, resources::atlas_ptr atlas,
                           std::uint16_t sprites_per_buffer /*= default_sprites_per_buffer*/)
    : scene_object(render_layer::overlay, scene_object_type::renderable, scene_manager)
    , sprites_per_buffer_(sprites_per_buffer)
    , sprite_vertex_data_(sprites_per_buffer * sizeof(sprite_vertex))
    , atlas_(atlas)
{
    __create_and_setup_vertex_buffer();
    __create_and_setup_index_buffer();

    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex), (void*)8);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex), (void*)16);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex), (void*)32);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex), (void*)48);
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex), (void*)64);
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex), (void*)80);
}

void sprite_batch::__add_sprite(sprite* spr)
{
    if (sprites_.size() >= sprites_per_buffer_)
        throw sprite_batch_full_exception();

    sprites_.push_back(spr);
}

void sprite_batch::__remove_sprite(sprite* spr)
{
    sprites_.erase(std::remove(sprites_.begin(), sprites_.end(), spr), sprites_.end());
}

void sprite_batch::__create_and_setup_vertex_buffer()
{
    gfx::buffer_manager &buffer_manager = scene_manager_->get_device().get_buffer_manager();
    vertex_buffer_ = buffer_manager.create_buffer(gfx::buffer_type::array);
    vertex_buffer_->set_data(0, nullptr, gfx::buffer_usage::stream_usage);
}

void sprite_batch::__create_and_setup_index_buffer()
{
    gfx::buffer_manager &buffer_manager = scene_manager_->get_device().get_buffer_manager();
    index_buffer_ = buffer_manager.create_buffer(gfx::buffer_type::element_array);

    std::vector<uint16_t> index_buffer_data(sprites_per_buffer_ * indices_per_sprite);
    uint16_t *index_buffer_data_ptr = index_buffer_data.data();

    std::uint16_t offset = 0;
    for (std::uint16_t i = 0; i < sprites_per_buffer_; ++i)
    {
        std::uint16_t index_offset = i * vertices_per_sprite;
        index_buffer_data_ptr[offset++] = index_offset;
        index_buffer_data_ptr[offset++] = index_offset + 1;
        index_buffer_data_ptr[offset++] = index_offset + 2;
        index_buffer_data_ptr[offset++] = index_offset + 2;
        index_buffer_data_ptr[offset++] = index_offset + 1;
        index_buffer_data_ptr[offset++] = index_offset + 3;
    }

    int buffer_size = static_cast<int>(index_buffer_data.size() * sizeof(uint16_t));
    index_buffer_->set_data(buffer_size, index_buffer_data.data(), gfx::buffer_usage::static_usage);
}

void sprite_batch::__sort_by_zorder()
{
    std::sort(sprites_.begin(), sprites_.end(), [](const sprite *a, const sprite *b)
        {
            return a->get_zorder() < b->get_zorder();
        }
    );
}

void sprite_batch::__fill_and_upload_sprite_data_buffer()
{
    sprite_vertex *vertex_data_ptr = reinterpret_cast<sprite_vertex *>(sprite_vertex_data_.data());

    int sprite_data_offset = 0;
    for (sprite *spr : sprites_)
    {
        glm::mat4 sprite_matrix = spr->get_matrix();
        resources::atlas_region region = spr->get_atlas_region();

        glm::vec2 size_2 = spr->get_size() * 0.5f;

        // Bottom left
        vertex_data_ptr[sprite_data_offset++] =
        {
            -size_2.x, size_2.y,
            region.u1, region.v2,
            1.0f, 1.0f, 1.0f, 1.0f,
            sprite_matrix
        };

        // Bottom right
        vertex_data_ptr[sprite_data_offset++] =
        {
            size_2.x, size_2.y,
            region.u2, region.v2,
            1.0f, 1.0f, 1.0f, 1.0f,
            sprite_matrix
        };

        // Top left
        vertex_data_ptr[sprite_data_offset++] =
        {
            -size_2.x, -size_2.y,
            region.u1, region.v1,
            1.0f, 1.0f, 1.0f, 1.0f,
            sprite_matrix
        };

        // Top right
        vertex_data_ptr[sprite_data_offset++] =
        {
            size_2.x, -size_2.y,
            region.u2, region.v1,
            1.0f, 1.0f, 1.0f, 1.0f,
            sprite_matrix
        };
    }

    int vertex_buffer_size = sprites_.size() * sizeof(sprite_vertex) * vertices_per_sprite;
    vertex_buffer_->set_data(vertex_buffer_size, vertex_data_ptr, gfx::buffer_usage::stream_usage);
}

void sprite_batch::render(const glm::mat4x4 &projection, const glm::mat4x4 &view,
    const glm::mat4x4 &model, float /*dt*/)
{
    __sort_by_zorder();
    __fill_and_upload_sprite_data_buffer();

    gfx::material_ptr material = atlas_->get_material();
    material->bind();

    vertex_buffer_->bind();
    index_buffer_->bind();

    material->get_shader()->set_projection_matrix(projection);
    material->get_shader()->set_model_matrix(model);
    material->get_shader()->set_view_matrix(view);

    glBindVertexArray(vao);

    glDrawRangeElements(GL_TRIANGLES, 0, sprites_.size() * indices_per_sprite,
        sprites_.size() * indices_per_sprite, GL_UNSIGNED_SHORT, nullptr);
}

} // namespace scene
} // namespace aeon
