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

#include <gfx/gfx_resource_manager.h>
#include <gfx/gfx_buffer_manager.h>
#include <gfx/gfx_sprite_batch.h>
#include <common/types/color.h>
#include <scene/viewport.h>
#include <memory>

namespace aeon
{
namespace gfx
{

struct buffer_clear_flag
{
    static const int color_buffer = 0x01;
    static const int depth_buffer = 0x02;
};

class device
{
public:
    device();

    virtual ~device() = default;

    void initialize();

    virtual void set_clear_color(const common::types::color &c) = 0;
    virtual void set_viewport(scene::viewport *vp) = 0;
    virtual void clear_buffer(int buffer_flag) = 0;

    virtual sprite_batch_ptr create_sprite_batch(material_ptr material, std::uint16_t sprites_per_buffer) = 0;

    texture_manager &get_texture_manager()
    {
        return *texture_manager_;
    }

    shader_manager &get_shader_manager()
    {
        return *shader_manager_;
    }

    material_manager &get_material_manager()
    {
        return *material_manager_;
    }

    buffer_manager &get_buffer_manager()
    {
        return *buffer_manager_;
    }

protected:
    virtual void __initialize_impl() = 0;

    bool initialized_;
    std::unique_ptr<texture_manager> texture_manager_;
    std::unique_ptr<shader_manager> shader_manager_;
    std::unique_ptr<material_manager> material_manager_;
    std::unique_ptr<buffer_manager> buffer_manager_;
};

} // namespace gfx
} // namespace aeon
