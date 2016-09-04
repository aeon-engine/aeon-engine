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
 
#include <gfx/null/gfx_null_sprite_batch.h>
#include <gfx/null/gfx_null_device.h>

namespace aeon
{
namespace gfx
{
namespace null
{

gfx_null_sprite_batch::gfx_null_sprite_batch(material_ptr material, std::uint16_t sprites_per_buffer)
    : gfx::sprite_batch(material, sprites_per_buffer)
{
}

void gfx_null_sprite_batch::upload_sprite_buffer(const sprite_vertex *, int)
{
}

void gfx_null_sprite_batch::render(const glm::mat4x4 &, const glm::mat4x4 &, const glm::mat4x4 &)
{
}

} // namespace null
} // namespace gfx
} // namespace aeon
