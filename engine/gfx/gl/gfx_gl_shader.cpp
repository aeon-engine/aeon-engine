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

#include <gfx/gl/gfx_gl_shader.h>
#include <glm/gtc/type_ptr.hpp>
#include <common/check_gl_error.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

shader::shader()
    : logger_(common::logger::get_singleton(), "Gfx::GL::Shader")
    , handle_(0)
    , projection_matrix_handle_(0)
    , model_matrix_handle_(0)
    , view_matrix_handle_(0)
    , texture0_handle_(0)
{
}

shader::~shader()
{
    AEON_LOG_TRACE(logger_) << "Deleting Program (GL handle: " << handle_ << ")." << std::endl;
    glDeleteProgram(handle_);
    AEON_CHECK_GL_ERROR();
}

void shader::bind() const
{
    glUseProgram(handle_);
    AEON_CHECK_GL_ERROR();
}

void shader::set_projection_matrix(const glm::mat4 &matrix)
{
    glUniformMatrix4fv(projection_matrix_handle_, 1, GL_FALSE, glm::value_ptr(matrix));
    AEON_CHECK_GL_ERROR();
}

void shader::set_model_matrix(const glm::mat4 &matrix)
{
    glUniformMatrix4fv(model_matrix_handle_, 1, GL_FALSE, glm::value_ptr(matrix));
    AEON_CHECK_GL_ERROR();
}

void shader::set_view_matrix(const glm::mat4 &matrix)
{
    glUniformMatrix4fv(view_matrix_handle_, 1, GL_FALSE, glm::value_ptr(matrix));
    AEON_CHECK_GL_ERROR();
}

} // namespace gl
} // namespace gfx
} // namespace aeon
