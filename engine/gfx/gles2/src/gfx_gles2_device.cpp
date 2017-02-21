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

#include <gfx/gles2/gfx_gles2_texture_manager.h>
#include <gfx/gles2/gfx_gles2_shader_manager.h>
#include <gfx/gles2/gfx_gles2_material_manager.h>
#include <gfx/gles2/gfx_gles2_buffer_manager.h>
#include <gfx/gles2/gfx_gles2_device.h>
#include <gfx/gles2/gfx_gles2_mesh.h>
#include <gfx/gl_common/check_gl_error.h>
#include <GLES2/gl2.h>
#include <memory>

namespace aeon
{
namespace gfx
{
namespace gles2
{

gfx_gles2_device::gfx_gles2_device()
    : logger_(common::logger::get_singleton(), "Gfx::GLES2::Device")
{
}

void gfx_gles2_device::__initialize_impl()
{
    AEON_LOG_MESSAGE(logger_) << "Initializing device." << std::endl;

    if (initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Initialize called while already initialized." << std::endl;
        throw gfx_gles2_initialized_exception();
    }

    texture_manager_ = std::make_unique<gfx_gles2_texture_manager>();
    shader_manager_ = std::make_unique<gfx_gles2_shader_manager>();
    material_manager_ = std::make_unique<gfx_gles2_material_manager>(*this);
    buffer_manager_ = std::make_unique<gfx_gles2_buffer_manager>();
    atlas_manager_ = std::make_unique<gfx_atlas_manager>();

    glEnable(GL_BLEND);
    AEON_CHECK_GL_ERROR();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    AEON_CHECK_GL_ERROR();

    initialized_ = true;
}

void gfx_gles2_device::set_clear_color(const common::types::color &c)
{
    glClearColor(c.r, c.g, c.b, c.a);
    AEON_CHECK_GL_ERROR();
}

void gfx_gles2_device::set_viewport(scene::viewport *vp)
{
    common::types::rectangle<int> rect = common::types::rectangle<int>(vp->get_rectangle());
    glViewport(rect.x, rect.y, rect.width, rect.height);
    AEON_CHECK_GL_ERROR();
}

void gfx_gles2_device::clear_buffer(int buffer_flag)
{
    GLenum buffers = 0;

    if ((buffer_flag & gfx::buffer_clear_flag::color_buffer) != 0)
        buffers |= GL_COLOR_BUFFER_BIT;

    if ((buffer_flag & gfx::buffer_clear_flag::depth_buffer) != 0)
        buffers |= GL_DEPTH_BUFFER_BIT;

    glClear(buffers);
    AEON_CHECK_GL_ERROR();
}

mesh_ptr gfx_gles2_device::create_mesh(material_ptr material)
{
    return std::make_unique<gfx_gles2_mesh>(this, material);
}

} // namespace gles2
} // namespace gfx
} // namespace aeon
