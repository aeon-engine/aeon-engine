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

#include <gfx/gl/gfx_gl_material_manager.h>
#include <gfx/gl/gfx_gl_material.h>
#include <gfx/gl/gfx_gl_device.h>
#include <resources/material.h>
#include <GL/glew.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

material_manager::material_manager(device &dev)
    : device_(dev)
{
}

material_ptr material_manager::__load(resources::material_ptr mat)
{
    texture_manager &texture_mgr = device_.get_texture_manager();
    shader_manager &shader_mgr = device_.get_shader_manager();

    material_gl_ptr m = std::make_shared<gl::material>();

    resources::image_ptr texture_image = mat->get_texture();
    m->texture_ = texture_mgr.load(texture_image);

    resources::shader_ptr shader_res = mat->get_shader();
    m->shader_ = shader_mgr.load(shader_res);

    return m;
}

} // namespace gl
} // namespace gfx
} // namespace aeon
