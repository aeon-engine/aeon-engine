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

#include <aeon/gfx/gfx_buffer.h>
#include <aeon/common/exception.h>
#include <aeon/logger/logger.h>
#include <GL/glew.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

DEFINE_EXCEPTION_OBJECT(gfx_opengl_buffer_exception, aeon::common::exception, "GL Buffer error");

class gfx_gl_buffer : public gfx::buffer
{
public:
    explicit gfx_gl_buffer(buffer_type type);
    virtual ~gfx_gl_buffer();

    void set_data(int size, const void *data, buffer_usage usage) override;

    void bind() override;

    auto has_data() const -> bool override;

private:
    auto __buffer_type_as_gl_enum() const -> GLenum;
    auto __buffer_usage_as_gl_enum(buffer_usage usage) const -> GLenum;

    logger::logger logger_;

    GLuint handle_;
    bool has_data_;
};

} // namespace gl
} // namespace gfx
} // namespace aeon
