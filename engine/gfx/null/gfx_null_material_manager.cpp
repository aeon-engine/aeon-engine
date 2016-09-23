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

#include <gfx/null/gfx_null_material_manager.h>
#include <gfx/null/gfx_null_material.h>
#include <gfx/null/gfx_null_device.h>
#include <resources/material.h>

namespace aeon
{
namespace gfx
{
namespace null
{

gfx_null_material_manager::gfx_null_material_manager(gfx_null_device &dev)
    : device_(dev)
{
}

material_ptr gfx_null_material_manager::create(const resources::material &mat)
{
    gfx::texture_manager &texture_mgr = device_.get_texture_manager();
    gfx::shader_manager &shader_mgr = device_.get_shader_manager();

    material_null_ptr m = std::make_shared<gfx_null_material>();

    resources::image_ptr texture_image = mat.get_texture();
    m->texture_ = std::dynamic_pointer_cast<gfx_null_texture>(texture_mgr.create(*texture_image));

    resources::shader_ptr shader_res = mat.get_shader();
    m->shader_ = std::dynamic_pointer_cast<gfx_null_shader>(shader_mgr.create(*shader_res));

    return m;
}

} // namespace null
} // namespace gfx
} // namespace aeon
