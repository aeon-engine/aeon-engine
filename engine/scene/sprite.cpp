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

sprite::sprite(gfx::texture_ptr texture)
    : size_(texture->get_size())
{
}

sprite::sprite(gfx::texture_ptr texture, glm::vec2 size)
    : size_(size)
{
}

sprite::sprite(gfx::texture_ptr texture, float width, float height)
    : size_(width, height)
{
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

} // namespace scene
} // namespace aeon
