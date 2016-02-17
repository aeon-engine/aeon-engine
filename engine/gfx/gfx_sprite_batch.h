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

#include <gfx/gfx_material.h>
#include <glm/mat4x4.hpp>
#include <common/exception.h>
#include <memory>

namespace aeon
{

namespace gfx
{

DEFINE_EXCEPTION_OBJECT(gfx_sprite_batch_exception, aeon::common::exception, "Sprite Batch exception.");
DEFINE_EXCEPTION_OBJECT(gfx_sprite_batch_full_exception, gfx_sprite_batch_exception,
                        "Sprite Batch full. Amount can not exceed maximum sprites per batch.");

struct sprite_vertex
{
    float x, y;
    float u, v;
    float r, g, b, a;
    glm::mat4x4 matrix;
};

class sprite_batch
{
public:
    static const std::uint16_t default_sprites_per_buffer = 512;
    static const int vertices_per_sprite = 4;
    static const std::uint16_t indices_per_sprite = 6;

    explicit sprite_batch(material_ptr material, std::uint16_t sprites_per_buffer = default_sprites_per_buffer);
    virtual ~sprite_batch() = default;

    virtual void upload_sprite_buffer(const sprite_vertex *sprite_vertex_data, int count) = 0;

    virtual void render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model) = 0;

protected:
    material_ptr material_;

    /*!
     * Determines how many sprites are stored to the vertex buffer per render.
     * This is the maximum amount of sprites that can be added to this batch.
     */
    std::uint16_t sprites_per_buffer_;
};

using sprite_batch_ptr = std::unique_ptr<sprite_batch>;

} // namespace gfx
} // namespace aeon
