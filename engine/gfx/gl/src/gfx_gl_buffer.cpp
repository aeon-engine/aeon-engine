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

#include <aeon/gfx/gl/gfx_gl_buffer.h>
#include <aeon/gfx/gl_common/check_gl_error.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

gfx_gl_buffer::gfx_gl_buffer(buffer_type type)
    : gfx::buffer(type)
    , logger_(common::logger::get_singleton(), "Gfx::GL::Buffer")
    , handle_(0)
    , has_data_(false)
{
    glGenBuffers(1, &handle_);
    AEON_CHECK_GL_ERROR();

    AEON_LOG_TRACE(logger_) << "Created buffer (GL handle: " << handle_ << ")." << std::endl;
}

gfx_gl_buffer::~gfx_gl_buffer()
{
    AEON_LOG_TRACE(logger_) << "Deleting buffer (GL handle: " << handle_ << ")." << std::endl;
    glDeleteBuffers(1, &handle_);
    AEON_CHECK_GL_ERROR();
}

void gfx_gl_buffer::set_data(int size, const void *data, buffer_usage usage)
{
    GLenum gl_type = __buffer_type_as_gl_enum();
    GLenum gl_usage = __buffer_usage_as_gl_enum(usage);

    glBindBuffer(gl_type, handle_);
    AEON_CHECK_GL_ERROR();

    glBufferData(gl_type, size, data, gl_usage);
    AEON_CHECK_GL_ERROR();

    has_data_ = true;
}

void gfx_gl_buffer::bind()
{
    glBindBuffer(__buffer_type_as_gl_enum(), handle_);
    AEON_CHECK_GL_ERROR();
}

auto gfx_gl_buffer::has_data() const -> bool
{
    return has_data_;
}

auto gfx_gl_buffer::__buffer_type_as_gl_enum() const -> GLenum
{
    switch (type_)
    {
        case buffer_type::array:
            return GL_ARRAY_BUFFER;
        case buffer_type::element_array:
            return GL_ELEMENT_ARRAY_BUFFER;
        default:
        {
            AEON_LOG_ERROR(logger_) << "Unknown or unsupported buffer type." << std::endl;
            throw gfx_opengl_buffer_exception();
        }
    }
}

auto gfx_gl_buffer::__buffer_usage_as_gl_enum(buffer_usage usage) const -> GLenum
{
    switch (usage)
    {
        case buffer_usage::stream_usage:
            return GL_STREAM_DRAW;
        case buffer_usage::static_usage:
            return GL_STATIC_DRAW;
        case buffer_usage::dynamic_usage:
            return GL_DYNAMIC_DRAW;
        default:
        {
            AEON_LOG_ERROR(logger_) << "Unknown or unsupported buffer usage." << std::endl;
            throw gfx_opengl_buffer_exception();
        }
    }
}

} // namespace gl
} // namespace gfx
} // namespace aeon
