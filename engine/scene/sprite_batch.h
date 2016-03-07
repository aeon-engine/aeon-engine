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

#include <resources/atlas.h>
#include <scene/scene_object.h>
#include <gfx/gfx_sprite_batch.h>
#include <common/buffer.h>
#include <vector>
#include <memory>

namespace aeon
{
namespace scene
{

class sprite;
class sprite_batch : public scene_object
{
    friend class sprite;

public:
    explicit sprite_batch(scene_manager &scene_manager, resources::atlas_ptr atlas,
                          std::uint16_t sprites_per_buffer = gfx::sprite_batch::default_sprites_per_buffer);
    virtual ~sprite_batch() = default;

private:
    void __add_sprite(sprite *spr);
    void __remove_sprite(sprite *spr);

    void __sort_by_zorder();

    void __fill_and_upload_sprite_data_buffer(float dt);

    void render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model, float dt) override;

    std::vector<sprite *> sprites_;
    common::buffer_u8 sprite_vertex_data_;

    gfx::sprite_batch_ptr sprite_batch_;
};

using sprite_batch_ptr = std::shared_ptr<sprite_batch>;

} // namespace scene
} // namespace aeon
