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

#include <gfx/gl/gfx_gl_buffer.h>
#include <common/check_gl_error.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

buffer::buffer(buffer_type type)
    : gfx::buffer(type)
    , logger_(common::logger::get_singleton(), "Gfx::GL::Buffer")
    , handle_(0)
{
    glGenBuffers(1, &handle_);
    AEON_CHECK_GL_ERROR();

    AEON_LOG_TRACE(logger_) << "Created buffer (GL handle: " << handle_ << ")." << std::endl;
}

buffer::~buffer()
{
    AEON_LOG_TRACE(logger_) << "Deleting buffer (GL handle: " << handle_ << ")." << std::endl;
    glDeleteBuffers(1, &handle_);
    AEON_CHECK_GL_ERROR();
}

void buffer::set_data(int size, const void *data, buffer_usage usage)
{
    GLenum gl_type = __buffer_type_as_gl_enum();
    GLenum gl_usage = __buffer_usage_as_gl_enum(usage);

    glBindBuffer(gl_type, handle_);
    AEON_CHECK_GL_ERROR();

    glBufferData(gl_type, size, data, gl_usage);
    AEON_CHECK_GL_ERROR();
}

void buffer::bind()
{
    glBindBuffer(__buffer_type_as_gl_enum(), handle_);
    AEON_CHECK_GL_ERROR();
}

GLenum buffer::__buffer_type_as_gl_enum() const
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

GLenum buffer::__buffer_usage_as_gl_enum(buffer_usage usage) const
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
