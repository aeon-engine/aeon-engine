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

#include <aeon/gfx/gl/gfx_gl_texture_manager.h>
#include <aeon/gfx/gl/gfx_gl_shader_manager.h>
#include <aeon/gfx/gl/gfx_gl_material_manager.h>
#include <aeon/gfx/gl/gfx_gl_buffer_manager.h>
#include <aeon/gfx/gl/gfx_gl_device.h>
#include <aeon/gfx/gl/gfx_gl_mesh.h>
#include <aeon/gfx/gl_common/check_gl_error.h>
#include <GL/glew.h>
#include <memory>

namespace aeon
{
namespace gfx
{
namespace gl
{

gfx_gl_device::gfx_gl_device(io::io_interface &io)
    : gfx::device(io)
    , logger_(common::logger::get_singleton(), "Gfx::GL::Device")
    , render_targets_()
{
}

gfx_gl_device::~gfx_gl_device() = default;

void gfx_gl_device::__initialize_impl()
{
    AEON_LOG_MESSAGE(logger_) << "Initializing device." << std::endl;

    if (initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Initialize called while already initialized." << std::endl;
        throw gl_initialized_exception();
    }

    initialized_ = true;
}

void gfx_gl_device::set_clear_color(const common::types::color &c)
{
    glClearColor(c.r, c.g, c.b, c.a);
    AEON_CHECK_GL_ERROR();
}

void gfx_gl_device::set_viewport(render_target &rt, viewport &vp)
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

void gfx_gl_device::clear_buffer(int buffer_flag)
{
    GLenum buffers = 0;

    if ((buffer_flag & gfx::buffer_clear_flag::color_buffer) != 0)
        buffers |= GL_COLOR_BUFFER_BIT;

    if ((buffer_flag & gfx::buffer_clear_flag::depth_buffer) != 0)
        buffers |= GL_DEPTH_BUFFER_BIT;

    glClear(buffers);
    AEON_CHECK_GL_ERROR();
}

auto gfx_gl_device::create_mesh(std::shared_ptr<material> material) -> std::unique_ptr<mesh>
{
    return std::make_unique<gfx_gl_mesh>(this, material);
}

void gfx_gl_device::add_render_target(std::shared_ptr<render_target> target)
{
    // HACK: If there are no render targets yet, this is the first window that is being opened.
    // This means we can initialize opengl here.
    if (render_targets_.empty())
    {
        __create_managers();
        __setup_opengl();
        __initialize_glew();
    }

    render_targets_.push_back(target);
}

auto gfx_gl_device::render(float dt) -> bool
{
    clear_buffer(gfx::buffer_clear_flag::color_buffer | gfx::buffer_clear_flag::depth_buffer);

    for (std::shared_ptr<render_target> &render_target : render_targets_)
    {
        if (!render_target->handle_frame(dt))
        {
            return false;
        }
    }

    return true;
}

void gfx_gl_device::set_scissor(const common::types::rectangle<float> &scissor) const
{
    glScissor(static_cast<GLsizei>(scissor.left()), static_cast<GLsizei>(scissor.top()),
              static_cast<GLsizei>(scissor.width()), static_cast<GLsizei>(scissor.height()));
    AEON_CHECK_GL_ERROR();
}

void gfx_gl_device::__create_managers()
{
    texture_manager_ = std::make_unique<gfx_gl_texture_manager>();
    shader_manager_ = std::make_unique<gfx_gl_shader_manager>();
    material_manager_ = std::make_unique<gfx_gl_material_manager>();
    buffer_manager_ = std::make_unique<gfx_gl_buffer_manager>();
    atlas_manager_ = std::make_unique<gfx_atlas_manager>();
}

void gfx_gl_device::__setup_opengl() const
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

void gfx_gl_device::__initialize_glew() const
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        AEON_LOG_FATAL(logger_) << "GLEW initialization failed." << std::endl;
        throw gl_device_exception();
    }

    // Squash all OpenGL errors from glewInit before continuing.
    __report_and_squash_glew_errors();
}

void gfx_gl_device::__report_and_squash_glew_errors() const
{
    int count = 0;
    while (glGetError() != GL_NO_ERROR)
    {
        if (count++ > 100)
        {
            AEON_LOG_FATAL(logger_) << "GLEW initialization reported too many OpenGL errors (> 100)." << std::endl;
            break;
        }
    }

    if (count > 0)
        AEON_LOG_WARNING(logger_) << "glewInit reported " << count << " OpenGL error(s)." << std::endl;
}

} // namespace gl
} // namespace gfx
} // namespace aeon
