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

#pragma once

#include <aeon/gfx/gfx_shader_manager.h>
#include <aeon/common/logger.h>
#include <aeon/common/exception.h>
#include <GLES2/gl2.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

DEFINE_EXCEPTION_OBJECT(gfx_gles2_shader_exception, aeon::common::exception, "GLES 2 shader exception.");
DEFINE_EXCEPTION_OBJECT(gfx_gles2_shader_compile_exception, gfx_gles2_shader_exception,
                        "GLES 2 shader compilation exception.");

class gfx_gles2_shader_manager : public gfx::shader_manager
{
public:
    gfx_gles2_shader_manager();
    virtual ~gfx_gles2_shader_manager() = default;

private:
    auto create(const data::shader &shader_data) -> std::shared_ptr<shader> override;

    auto __load_gl_shader(const std::string &source, GLenum type) const -> GLuint;
    auto __link_gl_program(GLuint vertexshader, GLuint fragmentshader) const -> GLuint;

    aeon::logger::logger logger_;
};

} // namespace gles2
} // namespace gfx
} // namespace aeon
