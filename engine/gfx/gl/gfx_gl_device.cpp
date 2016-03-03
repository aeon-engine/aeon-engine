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

#include <gfx/gl/gfx_gl_texture_manager.h>
#include <gfx/gl/gfx_gl_shader_manager.h>
#include <gfx/gl/gfx_gl_material_manager.h>
#include <gfx/gl/gfx_gl_buffer_manager.h>
#include <gfx/gl/gfx_gl_device.h>
#include <gfx/gl/gfx_gl_sprite_batch.h>
#include <GL/glew.h>
#include <memory>
#include <common/check_gl_error.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

device::device()
    : logger_(common::logger::get_singleton(), "Gfx::GL::Device")
{
}

void device::__initialize_impl()
{
    AEON_LOG_MESSAGE(logger_) << "Initializing device." << std::endl;

    if (initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Initialize called while already initialized." << std::endl;
        throw gl_initialized_exception();
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        AEON_LOG_FATAL(logger_) << "GLEW initialization failed. Did you create a render window first?" << std::endl;
        throw gl_device_exception();
    }

    texture_manager_ = std::make_unique<gl::texture_manager>();
    shader_manager_ = std::make_unique<gl::shader_manager>();
    material_manager_ = std::make_unique<gl::material_manager>(*this);
    buffer_manager_ = std::make_unique<gl::buffer_manager>();

    glEnable(GL_BLEND);
    AEON_CHECK_GL_ERROR();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    AEON_CHECK_GL_ERROR();

    initialized_ = true;
}

void device::set_clear_color(const common::types::color &c)
{
    glClearColor(c.r, c.g, c.b, c.a);
    AEON_CHECK_GL_ERROR();
}

void device::set_viewport(scene::viewport *vp)
{
    common::types::rectangle<int> rect = common::types::rectangle<int>(vp->get_rectangle());
    glViewport(rect.x, rect.y, rect.width, rect.height);
    AEON_CHECK_GL_ERROR();
}

void device::clear_buffer(int buffer_flag)
{
    GLenum buffers = 0;

    if ((buffer_flag & gfx::buffer_clear_flag::color_buffer) != 0)
        buffers |= GL_COLOR_BUFFER_BIT;

    if ((buffer_flag & gfx::buffer_clear_flag::depth_buffer) != 0)
        buffers |= GL_DEPTH_BUFFER_BIT;

    glClear(buffers);
    AEON_CHECK_GL_ERROR();
}

sprite_batch_ptr device::create_sprite_batch(material_ptr material, std::uint16_t sprites_per_buffer)
{
    return std::make_unique<sprite_batch>(this, material, sprites_per_buffer);
}

} // namespace gl
} // namespace gfx
} // namespace aeon
