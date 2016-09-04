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

#include <gfx/gfx_sprite_batch.h>

namespace aeon
{
namespace gfx
{
namespace null
{

class gfx_null_device;
class gfx_null_sprite_batch : public gfx::sprite_batch
{
public:
    explicit gfx_null_sprite_batch(material_ptr material, std::uint16_t sprites_per_buffer);
    virtual ~gfx_null_sprite_batch() = default;

    void upload_sprite_buffer(const sprite_vertex *sprite_vertex_data, int count) override;

    void render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model) override;

};

} // namespace null
} // namespace gfx
} // namespace aeon
