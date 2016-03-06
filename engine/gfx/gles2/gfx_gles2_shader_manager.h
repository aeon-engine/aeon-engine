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

#include <gfx/gfx_resource_manager.h>
#include <common/logger.h>
#include <common/exception.h>
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

DEFINE_EXCEPTION_OBJECT(gfx_opengl_shader_exception, aeon::common::exception, "OpenGL shader exception.");
DEFINE_EXCEPTION_OBJECT(gfx_opengl_shader_compile_exception, gfx_opengl_shader_exception,
                        "OpenGL shader compilation exception.");

class shader_manager : public gfx::shader_manager
{
public:
    shader_manager();
    virtual ~shader_manager() = default;

private:
    shader_ptr __load(resources::shader_ptr shader) override;

    GLuint __load_gl_shader(const std::string &source, GLenum type);
    GLuint __link_gl_program(GLuint vertexshader, GLuint fragmentshader);

    aeon::logger::logger logger_;
};

} // namespace gles2
} // namespace gfx
} // namespace aeon
