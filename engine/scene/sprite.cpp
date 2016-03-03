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
#include <scene/sprite_batch.h>

namespace aeon
{
namespace scene
{

sprite::sprite(scene_manager *scene_manager, sprite_batch_ptr batch, const resources::atlas_region &region, int zorder)
    : scene_object(render_layer::overlay, scene_object_type::spatial, scene_manager)
    , has_z_order(zorder)
    , size_(region.size)
    , region_(region)
    , batch_(batch)
{
    batch_->__add_sprite(this);
}

sprite::sprite(scene_manager *scene_manager, sprite_batch_ptr batch, const resources::atlas_region &region,
               glm::vec2 size, int zorder)
    : scene_object(render_layer::overlay, scene_object_type::spatial, scene_manager)
    , has_z_order(zorder)
    , size_(size)
    , region_(region)
    , batch_(batch)
{
    batch_->__add_sprite(this);
}

sprite::~sprite()
{
    batch_->__remove_sprite(this);
}

void sprite::set_default_size()
{
    size_ = region_.size;
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

void sprite::set_atlas_region(const resources::atlas_region &region)
{
    region_ = region;
}

resources::atlas_region sprite::get_atlas_region() const
{
    return region_;
}

} // namespace scene
} // namespace aeon
