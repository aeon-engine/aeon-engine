/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <gfx/gles2/gfx_gles2_material_manager.h>
#include <gfx/gles2/gfx_gles2_material.h>
#include <gfx/gles2/gfx_gles2_device.h>
#include <resources/material.h>
#include <GLES2/gl2.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

gfx_gles2_material_manager::gfx_gles2_material_manager(gfx_gles2_device &dev)
    : device_(dev)
{
}

material_ptr gfx_gles2_material_manager::__load(resources::material_ptr mat)
{
    gfx::texture_manager &texture_mgr = device_.get_texture_manager();
    gfx::shader_manager &shader_mgr = device_.get_shader_manager();

    gfx_gles2_material_ptr m = std::make_shared<gfx_gles2_material>();

    resources::image_ptr texture_image = mat->get_texture();
    m->texture_ = std::dynamic_pointer_cast<gfx_gles2_texture>(texture_mgr.load(texture_image));

    resources::shader_ptr shader_res = mat->get_shader();
    m->shader_ = std::dynamic_pointer_cast<gfx_gles2_shader>(shader_mgr.load(shader_res));

    return m;
}

} // namespace gles2
} // namespace gfx
} // namespace aeon
