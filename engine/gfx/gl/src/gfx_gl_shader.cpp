/*
 * Copyright (c) 2012-2018 Robin Degen
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

#include <aeon/gfx/gl/gfx_gl_shader.h>
#include <aeon/gfx/gl_common/check_gl_error.h>
#include <aeon/common/logger.h>
#include <glm/gtc/type_ptr.hpp>

namespace aeon
{
namespace gfx
{
namespace gl
{

gfx_gl_shader::gfx_gl_shader()
    : logger_(common::logger::get_singleton(), "Gfx::GL::Shader")
    , handle_(0)
    , projection_matrix_handle_(0)
    , model_matrix_handle_(0)
    , view_matrix_handle_(0)
{
}

gfx_gl_shader::~gfx_gl_shader()
{
    AEON_LOG_TRACE(logger_) << "Deleting Program (GL handle: " << handle_ << ")." << std::endl;
    glDeleteProgram(handle_);
    AEON_CHECK_GL_ERROR();
}

void gfx_gl_shader::bind() const
{
    glUseProgram(handle_);
    AEON_CHECK_GL_ERROR();
}

void gfx_gl_shader::set_projection_matrix(const glm::mat4 &matrix)
{
    glUniformMatrix4fv(projection_matrix_handle_, 1, GL_FALSE, glm::value_ptr(matrix));
    AEON_CHECK_GL_ERROR();
}

void gfx_gl_shader::set_model_matrix(const glm::mat4 &matrix)
{
    glUniformMatrix4fv(model_matrix_handle_, 1, GL_FALSE, glm::value_ptr(matrix));
    AEON_CHECK_GL_ERROR();
}

void gfx_gl_shader::set_view_matrix(const glm::mat4 &matrix)
{
    glUniformMatrix4fv(view_matrix_handle_, 1, GL_FALSE, glm::value_ptr(matrix));
    AEON_CHECK_GL_ERROR();
}

auto gfx_gl_shader::get_sampler_handle_by_name(const std::string &name) const -> GLint
{
    auto handle = glGetUniformLocation(handle_, name.c_str());
    AEON_CHECK_GL_ERROR();

    return handle;
}

void gfx_gl_shader::bind_sampler(const GLint handle, const int bind_point) const
{
    glUniform1i(handle, bind_point);
    AEON_CHECK_GL_ERROR();
}

} // namespace gl
} // namespace gfx
} // namespace aeon
