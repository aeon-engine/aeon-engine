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

#include <aeon/gfx/gles2/gfx_gles2_texture_manager.h>
#include <aeon/gfx/gles2/gfx_gles2_shader_manager.h>
#include <aeon/gfx/gles2/gfx_gles2_material_manager.h>
#include <aeon/gfx/gles2/gfx_gles2_buffer_manager.h>
#include <aeon/gfx/gles2/gfx_gles2_device.h>
#include <aeon/gfx/gles2/gfx_gles2_mesh.h>
#include <memory>
#include <aeon/gfx/gl_common/check_gl_error.h>

#include <GLES2/gl2.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

gfx_gles2_device::gfx_gles2_device(io::io_interface &io)
    : gfx::device(io)
    , logger_(common::logger::get_singleton(), "Gfx::Gles2::Device")
    , render_targets_()
{
}

gfx_gles2_device::~gfx_gles2_device() = default;

void gfx_gles2_device::__initialize_impl()
{
    AEON_LOG_MESSAGE(logger_) << "Initializing device." << std::endl;

    if (initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Initialize called while already initialized." << std::endl;
        throw gles2_initialized_exception();
    }

    initialized_ = true;
}

void gfx_gles2_device::set_clear_color(const common::types::color &c)
{
    glClearColor(c.r, c.g, c.b, c.a);
    AEON_CHECK_GL_ERROR();
}

void gfx_gles2_device::set_viewport(render_target &rt, viewport &vp)
{
    common::types::rectangle<float> vp_rel_rect = vp.get_rectangle();
    glm::vec2 framebuffer_size = rt.get_framebuffer_size();
    common::types::rectangle<int> vp_abs_rect = {static_cast<int>(vp_rel_rect.left() * framebuffer_size.x),
                                                 static_cast<int>(vp_rel_rect.top() * framebuffer_size.y),
                                                 static_cast<int>(vp_rel_rect.right() * framebuffer_size.x),
                                                 static_cast<int>(vp_rel_rect.bottom() * framebuffer_size.y)};

    glViewport(vp_abs_rect.left(), vp_abs_rect.top(), vp_abs_rect.right(), vp_abs_rect.bottom());
    AEON_CHECK_GL_ERROR();

    glScissor(vp_abs_rect.left(), vp_abs_rect.top(), vp_abs_rect.right(), vp_abs_rect.bottom());
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

auto gfx_gles2_device::create_mesh(std::shared_ptr<material> material) -> std::unique_ptr<mesh>
{
    return std::make_unique<gfx_gles2_mesh>(this, material);
}

void gfx_gles2_device::add_render_target(std::shared_ptr<render_target> target)
{
    // HACK: If there are no render targets yet, this is the first window that is being opened.
    // This means we can initialize opengl here.
    if (render_targets_.empty())
    {
        __create_managers();
        __setup_opengl();
    }

    render_targets_.push_back(target);
}

auto gfx_gles2_device::render(float dt) -> bool
{
    clear_buffer(gfx::buffer_clear_flag::color_buffer | gfx::buffer_clear_flag::depth_buffer);

    for (auto &render_target : render_targets_)
    {
        if (!render_target->handle_frame(dt))
        {
            return false;
        }
    }

    return true;
}

void gfx_gles2_device::set_scissor(const common::types::rectangle<float> &scissor) const
{
    glScissor(static_cast<GLsizei>(scissor.left()), static_cast<GLsizei>(scissor.top()),
              static_cast<GLsizei>(scissor.width()), static_cast<GLsizei>(scissor.height()));
    AEON_CHECK_GL_ERROR();
}

void gfx_gles2_device::__create_managers()
{
    texture_manager_ = std::make_unique<gfx_gles2_texture_manager>();
    shader_manager_ = std::make_unique<gfx_gles2_shader_manager>();
    material_manager_ = std::make_unique<gfx_gles2_material_manager>();
    buffer_manager_ = std::make_unique<gfx_gles2_buffer_manager>();
    atlas_manager_ = std::make_unique<gfx_atlas_manager>();
}

void gfx_gles2_device::__setup_opengl() const
{
    glEnable(GL_DEPTH_TEST);
    AEON_CHECK_GL_ERROR();

    glDepthFunc(GL_LESS);
    AEON_CHECK_GL_ERROR();

    glEnable(GL_BLEND);
    AEON_CHECK_GL_ERROR();

    glEnable(GL_SCISSOR_TEST);
    AEON_CHECK_GL_ERROR();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    AEON_CHECK_GL_ERROR();

    glEnable(GL_CULL_FACE);
    AEON_CHECK_GL_ERROR();

    glCullFace(GL_BACK);
    AEON_CHECK_GL_ERROR();

    glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    AEON_CHECK_GL_ERROR();
}

} // namespace gles2
} // namespace gfx
} // namespace aeon
