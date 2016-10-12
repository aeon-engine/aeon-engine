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

#include <aeon/gfx/gl/gfx_gl_vertex_array_object.h>
#include <aeon/gfx/gl_common/check_gl_error.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

gfx_gl_vertex_array_object::gfx_gl_vertex_array_object(const vertex_attributes &attributes)
    : logger_(common::logger::get_singleton(), "Gfx::GL::VertexArrayObject")
    , handle_(0)
{
    glGenVertexArrays(1, &handle_);
    AEON_CHECK_GL_ERROR();

    AEON_LOG_TRACE(logger_) << "Created Vertex Array Object (GL handle: " << handle_ << ")." << std::endl;

    glBindVertexArray(handle_);
    AEON_CHECK_GL_ERROR();

    int attrib_index = 0;
    for (auto attribute : attributes)
    {
        glEnableVertexAttribArray(attrib_index);
        AEON_CHECK_GL_ERROR();

        glVertexAttribPointer(attrib_index, attribute.size, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(attribute.stride),
                              reinterpret_cast<void *>(attribute.offset));
        AEON_CHECK_GL_ERROR();

        ++attrib_index;
    }
}

gfx_gl_vertex_array_object::~gfx_gl_vertex_array_object()
{
    AEON_LOG_TRACE(logger_) << "Deleting Vertex Array Object (GL handle: " << handle_ << ")." << std::endl;
    glDeleteVertexArrays(1, &handle_);
    AEON_CHECK_GL_ERROR();
}

void gfx_gl_vertex_array_object::bind() const
{
    glBindVertexArray(handle_);
    AEON_CHECK_GL_ERROR();
}

} // namespace gl
} // namespace gfx
} // namespace aeon