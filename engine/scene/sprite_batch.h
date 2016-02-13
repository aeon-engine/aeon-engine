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

#include <scene/scene_object.h>
#include <gfx/gfx_buffer.h>
#include <common/buffer.h>
#include <common/exception.h>
#include <vector>
#include <memory>

namespace aeon
{
namespace scene
{

DEFINE_EXCEPTION_OBJECT(sprite_batch_exception, aeon::common::exception, "Sprite Batch exception.");
DEFINE_EXCEPTION_OBJECT(sprite_batch_full_exception, sprite_batch_exception, "Sprite Batch full. Amount can not exceed maximum sprites per batch.");

struct sprite_vertex
{
    float x, y;
    float u, v;
    float r, g, b, a;
    glm::mat4x4 matrix;
};

class sprite;
class sprite_batch : public scene_object
{
    friend class sprite;

public:
    static const std::uint16_t default_sprites_per_buffer = 512;
    static const int vertices_per_sprite = 4;
    static const std::uint16_t indices_per_sprite = 6;

    explicit sprite_batch(scene_manager *scene_manager, gfx::material_ptr material, std::uint16_t sprites_per_buffer = default_sprites_per_buffer);
    virtual ~sprite_batch() = default;

private:
    void __add_sprite(sprite *spr);
    void __remove_sprite(sprite *spr);

    void __create_and_setup_vertex_buffer();
    void __create_and_setup_index_buffer();
    void __sort_by_zorder();

    void __fill_and_upload_sprite_data_buffer();

    virtual void render(const glm::mat4x4 &projection, const glm::mat4x4 &view,
        const glm::mat4x4 &model, float dt) override;

    /*!
     * Determines how many sprites are stored to the vertex buffer per render.
     * This is the maximum amount of sprites that can be added to this batch.
     */
    std::uint16_t sprites_per_buffer_;

    std::vector<sprite *> sprites_;
    common::buffer_u8 sprite_vertex_data_;

    gfx::buffer_ptr vertex_buffer_;
    gfx::buffer_ptr index_buffer_;

    gfx::material_ptr material_;
};

using sprite_batch_ptr = std::shared_ptr<sprite_batch>;

} // namespace scene
} // namespace aeon
