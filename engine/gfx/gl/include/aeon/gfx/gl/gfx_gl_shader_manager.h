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

#include <aeon/gfx/gfx_shader_manager.h>
#include <GL/glew.h>
#include <aeon/common/logger.h>
#include <aeon/common/exception.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

DEFINE_EXCEPTION_OBJECT(gfx_opengl_shader_exception, aeon::common::exception, "OpenGL shader exception.");
DEFINE_EXCEPTION_OBJECT(gfx_opengl_shader_compile_exception, gfx_opengl_shader_exception,
                        "OpenGL shader compilation exception.");

class gfx_gl_shader_manager : public gfx::shader_manager
{
public:
    gfx_gl_shader_manager();
    virtual ~gfx_gl_shader_manager() = default;

private:
    std::shared_ptr<shader> create(const data::shader &shader_data) override;

    GLuint __load_gl_shader(const std::string &source, GLenum type);
    GLuint __link_gl_program(GLuint vertexshader, GLuint fragmentshader);

    aeon::logger::logger logger_;
};

} // namespace gl
} // namespace gfx
} // namespace aeon
