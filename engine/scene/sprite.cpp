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

sprite::sprite(gfx::texture_ptr texture, int zorder /* = 0*/)
    : render_object(render_layer::overlay)
    , has_z_order(zorder)
    , size_(texture->get_size())
    , texture_(texture)
{
}

sprite::sprite(gfx::texture_ptr texture, glm::vec2 size, int zorder /* = 0*/)
    : render_object(render_layer::overlay)
    , has_z_order(zorder)
    , size_(size)
    , texture_(texture)
{
}

sprite::sprite(gfx::texture_ptr texture, float width, float height, int zorder /* = 0*/)
    : render_object(render_layer::overlay)
    , has_z_order(zorder)
    , size_(width, height)
    , texture_(texture)
{
}

sprite::~sprite()
{
}

void sprite::set_default_size()
{
    size_ = texture_->get_size();
}

void sprite::set_size(glm::vec2 size)
{
    size_ = size;
}

void sprite::set_size(float width, float height)
{
    size_ = glm::vec2(width, height);
}

void sprite::set_texture(gfx::texture_ptr texture)
{
    texture_ = texture;
}

gfx::texture_ptr sprite::get_texture() const
{
    return texture_;
}

int sprite::get_priority()
{
    return get_zorder();
}

} // namespace scene
} // namespace aeon
