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

#include <scene/sprite.h>

namespace aeon
{
namespace scene
{

sprite::sprite(gfx::material_ptr material, int zorder /* = 0*/)
    : render_object(render_layer::overlay)
    , has_z_order(zorder)
    , size_(material->get_texture()->get_size())
    , material_(material)
{
}

sprite::sprite(gfx::material_ptr material, glm::vec2 size, int zorder /* = 0*/)
    : render_object(render_layer::overlay)
    , has_z_order(zorder)
    , size_(size)
    , material_(material)
{
}

sprite::sprite(gfx::material_ptr material, float width, float height, int zorder /* = 0*/)
    : render_object(render_layer::overlay)
    , has_z_order(zorder)
    , size_(width, height)
    , material_(material)
{
}

void sprite::set_default_size()
{
    size_ = material_->get_texture()->get_size();
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

void sprite::set_material(gfx::material_ptr texture)
{
    material_ = texture;
}

gfx::material_ptr sprite::get_material() const
{
    return material_;
}

int sprite::get_priority()
{
    return get_zorder();
}

} // namespace scene
} // namespace aeon
