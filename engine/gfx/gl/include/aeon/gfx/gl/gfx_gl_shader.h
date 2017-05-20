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

#pragma once

#include <aeon/gfx/gfx_shader.h>
#include <aeon/logger/logger.h>
#include <GL/glew.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

class gfx_gl_shader : public gfx::shader
{
    friend class gfx_gl_shader_manager;

public:
    gfx_gl_shader();
    ~gfx_gl_shader() override;

    void bind() const;

    void set_projection_matrix(const glm::mat4 &matrix) override;
    void set_model_matrix(const glm::mat4 &matrix) override;
    void set_view_matrix(const glm::mat4 &matrix) override;

    auto get_sampler_handle_by_name(const std::string &name) const -> GLint;
    void bind_sampler(const GLint handle, const int bind_point) const;

private:
    logger::logger logger_;

    GLuint handle_;

    GLint projection_matrix_handle_;
    GLint model_matrix_handle_;
    GLint view_matrix_handle_;
};

} // namespace gl
} // namespace gfx
} // namespace aeon
