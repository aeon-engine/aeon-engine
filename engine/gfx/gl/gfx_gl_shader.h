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

#include <GL/glew.h>
#include <gfx/gfx_shader.h>
#include <common/logger.h>
#include <memory>

namespace aeon
{
namespace gfx
{
namespace gl
{

class shader : public gfx::shader
{
    friend class shader_manager;

public:
    shader();
    ~shader() override;

    void bind() const;

    void set_projection_matrix(const glm::mat4 &matrix) override;
    void set_model_matrix(const glm::mat4 &matrix) override;
    void set_view_matrix(const glm::mat4 &matrix) override;

private:
    aeon::logger::logger logger_;

    GLuint handle_;

    GLint projection_matrix_handle_;
    GLint model_matrix_handle_;
    GLint view_matrix_handle_;
    GLint texture0_handle_;
};

using shader_gl_ptr = std::shared_ptr<gl::shader>;

} // namespace gl
} // namespace gfx
} // namespace aeon
