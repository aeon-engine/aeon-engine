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

#include <common/has_z_order.h>
#include <scene/render_object.h>
#include <gfx/gfx_texture.h>
#include <glm/vec2.hpp>
#include <memory>

namespace aeon
{
namespace scene
{

class sprite : public render_object, public common::has_z_order
{
public:
    explicit sprite(gfx::texture_ptr texture, int zorder = 0);
    explicit sprite(gfx::texture_ptr texture, glm::vec2 size, int zorder = 0);
    explicit sprite(gfx::texture_ptr texture, float width, float height, int zorder = 0);

    virtual ~sprite() = default;

    void set_default_size();

    void set_size(glm::vec2 size);
    void set_size(float width, float height);

    glm::vec2 get_size() const;

    void set_texture(gfx::texture_ptr texture);
    gfx::texture_ptr get_texture() const;

    int get_priority() override;

private:
    glm::vec2 size_;
    gfx::texture_ptr texture_;
};

using sprite_ptr = std::shared_ptr<sprite>;

} // namespace scene
} // namespace aeon