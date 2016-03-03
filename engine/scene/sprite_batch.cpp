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

namespace aeon
{
namespace scene
{

sprite_batch::sprite_batch(scene_manager *scene_manager, resources::atlas_ptr atlas,
                           std::uint16_t sprites_per_buffer /*= default_sprites_per_buffer*/)
    : scene_object(render_layer::overlay, scene_object_type::renderable, scene_manager)
    , sprite_vertex_data_(sprites_per_buffer * sizeof(gfx::sprite_vertex))
{
    sprite_batch_ = scene_manager->get_device().create_sprite_batch(atlas->get_material(), sprites_per_buffer);
}

void sprite_batch::__add_sprite(sprite *spr)
{
    sprites_.push_back(spr);
}

void sprite_batch::__remove_sprite(sprite *spr)
{
    sprites_.erase(std::remove(sprites_.begin(), sprites_.end(), spr), sprites_.end());
}

void sprite_batch::__sort_by_zorder()
{
    std::sort(sprites_.begin(), sprites_.end(), [](const sprite *a, const sprite *b)
              {
                  return a->get_zorder() < b->get_zorder();
              });
}

void sprite_batch::__fill_and_upload_sprite_data_buffer(float dt)
{
    gfx::sprite_vertex *vertex_data_ptr = reinterpret_cast<gfx::sprite_vertex *>(sprite_vertex_data_.data());

    int sprite_data_offset = 0;
    for (sprite *spr : sprites_)
    {
        spr->update(dt);

        glm::mat4 sprite_matrix = spr->get_scene_matrix();
        resources::atlas_region region = spr->get_atlas_region();

        glm::vec2 size_2 = spr->get_size() * 0.5f;

        // Bottom left
        vertex_data_ptr[sprite_data_offset++] = {-size_2.x, size_2.y, region.u1, region.v2,    1.0f,
                                                 1.0f,      1.0f,     1.0f,      sprite_matrix};

        // Bottom right
        vertex_data_ptr[sprite_data_offset++] = {size_2.x, size_2.y, region.u2, region.v2,    1.0f,
                                                 1.0f,     1.0f,     1.0f,      sprite_matrix};

        // Top left
        vertex_data_ptr[sprite_data_offset++] = {-size_2.x, -size_2.y, region.u1, region.v1,    1.0f,
                                                 1.0f,      1.0f,      1.0f,      sprite_matrix};

        // Top right
        vertex_data_ptr[sprite_data_offset++] = {size_2.x, -size_2.y, region.u2, region.v1,    1.0f,
                                                 1.0f,     1.0f,      1.0f,      sprite_matrix};
    }

    sprite_batch_->upload_sprite_buffer(vertex_data_ptr, static_cast<int>(sprites_.size()));
}

void sprite_batch::render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model, float dt)
{
    __sort_by_zorder();
    __fill_and_upload_sprite_data_buffer(dt);

    sprite_batch_->render(projection, view, model);
}

} // namespace scene
} // namespace aeon
