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

#include <gfx/gles2/gfx_gles2_shader.h>
#include <glm/gtc/type_ptr.hpp>
#include <gfx/gl_common/check_gl_error.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

gfx_gles2_shader::gfx_gles2_shader()
    : logger_(common::logger::get_singleton(), "Gfx::GLES2::Shader")
    , handle_(0)
    , projection_matrix_handle_(0)
    , model_matrix_handle_(0)
    , view_matrix_handle_(0)
    , texture0_handle_(0)
{
}

gfx_gles2_shader::~gfx_gles2_shader()
{
    AEON_LOG_TRACE(logger_) << "Deleting Program (GL handle: " << handle_ << ")." << std::endl;
    glDeleteProgram(handle_);
    AEON_CHECK_GL_ERROR();
}

void gfx_gles2_shader::bind() const
{
    glUseProgram(handle_);
    AEON_CHECK_GL_ERROR();
}

void gfx_gles2_shader::set_projection_matrix(const glm::mat4 &matrix)
{
    glUniformMatrix4fv(projection_matrix_handle_, 1, GL_FALSE, glm::value_ptr(matrix));
    AEON_CHECK_GL_ERROR();
}

void gfx_gles2_shader::set_model_matrix(const glm::mat4 &matrix)
{
    glUniformMatrix4fv(model_matrix_handle_, 1, GL_FALSE, glm::value_ptr(matrix));
    AEON_CHECK_GL_ERROR();
}

void gfx_gles2_shader::set_view_matrix(const glm::mat4 &matrix)
{
    glUniformMatrix4fv(view_matrix_handle_, 1, GL_FALSE, glm::value_ptr(matrix));
    AEON_CHECK_GL_ERROR();
}

GLint gfx_gles2_shader::get_texture0_handle() const
{
    return texture0_handle_;
}

} // namespace gles2
} // namespace gfx
} // namespace aeon
