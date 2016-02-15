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
#include <GL/glew.h>
#include <memory>

namespace aeon
{
namespace gfx
{
namespace gl
{

void device::__initialize_impl()
{
    if (initialized_)
        throw gl_initialized_exception();

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        throw gl_device_exception();

    texture_manager_ = std::make_unique<gl::texture_manager>();
    shader_manager_ = std::make_unique<gl::shader_manager>();
    material_manager_ = std::make_unique<gl::material_manager>(*this);
    buffer_manager_ = std::make_unique<gl::buffer_manager>();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    initialized_ = true;
}

void device::set_clear_color(const common::types::color &c)
{
    glClearColor(c.r, c.g, c.b, c.a);
}

void device::set_viewport(scene::viewport *vp)
{
    common::types::rectangle<float> rect = vp->get_rectangle();

    glViewport(static_cast<int>(rect.left), static_cast<int>(rect.top), rect.width<int>(), rect.height<int>());
}

} // namespace gl
} // namespace gfx
} // namespace aeon
