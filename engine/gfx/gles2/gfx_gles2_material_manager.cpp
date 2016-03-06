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

#include <gfx/gles2/gfx_gles2_material_manager.h>
#include <gfx/gles2/gfx_gles2_material.h>
#include <gfx/gles2/gfx_gles2_device.h>
#include <resources/material.h>

#include <build_config.h>
#ifdef AEON_PLATFORM_IOS
#include <OpenGLES/ES2/gl.h>
#else
#include <GLES2/gl2.h>
#endif // AEON_PLATFORM_IOS

namespace aeon
{
namespace gfx
{
namespace gles2
{

material_manager::material_manager(device &dev)
    : device_(dev)
{
}

material_ptr material_manager::__load(resources::material_ptr mat)
{
    gfx::texture_manager &texture_mgr = device_.get_texture_manager();
    gfx::shader_manager &shader_mgr = device_.get_shader_manager();

    material_gl_ptr m = std::make_shared<gles2::material>();

    resources::image_ptr texture_image = mat->get_texture();
    m->texture_ = std::dynamic_pointer_cast<gles2::texture>(texture_mgr.load(texture_image));

    resources::shader_ptr shader_res = mat->get_shader();
    m->shader_ = std::dynamic_pointer_cast<gles2::shader>(shader_mgr.load(shader_res));

    return m;
}

} // namespace gles2
} // namespace gfx
} // namespace aeon
