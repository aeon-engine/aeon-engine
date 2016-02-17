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

#include <gfx/gl/gfx_gl_vertex_array_object.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

vertex_array_object::vertex_array_object(const vertex_attributes &attributes)
    : handle_(0)
{
    glGenVertexArrays(1, &handle_);
    glBindVertexArray(handle_);

    int attrib_index = 0;
    for (auto attribute : attributes)
    {
        glEnableVertexAttribArray(attrib_index);
        glVertexAttribPointer(attrib_index, attribute.size, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(attribute.stride),
                              reinterpret_cast<void *>(attribute.offset));
        ++attrib_index;
    }
}

vertex_array_object::~vertex_array_object()
{
    glDeleteVertexArrays(1, &handle_);
}

void vertex_array_object::bind() const
{
    glBindVertexArray(handle_);
}

} // namespace gl
} // namespace gfx
} // namespace aeon
