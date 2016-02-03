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

#include <gfx/gfx_texture_manager.h>
#include <gfx/gfx_shader_manager.h>
#include <gfx/gfx_material_manager.h>
#include <common/types/color.h>
#include <scene/viewport.h>
#include <memory>

namespace aeon
{
namespace gfx
{

class device
{
public:
    device();

    virtual ~device() = default;

    void initialize();

    virtual void set_clear_color(const common::types::color &c) = 0;
    virtual void set_viewport(scene::viewport *vp) = 0;

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

protected:
    virtual void __initialize_impl() = 0;

    bool initialized_;
    std::unique_ptr<texture_manager> texture_manager_;
    std::unique_ptr<shader_manager> shader_manager_;
    std::unique_ptr<material_manager> material_manager_;
};

} // namespace gfx
} // namespace aeon
