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

#include <aeon/gfx/gl/gfx_gl_vertex_array_object.h>
#include <aeon/gfx/gl_common/check_gl_error.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

gfx_gl_vertex_array_object::gfx_gl_vertex_array_object(const vertex_attributes &attributes,
                                                       std::shared_ptr<buffer> vertex_buffer,
                                                       std::shared_ptr<buffer> index_buffer)
    : logger_(common::logger::get_singleton(), "Gfx::GL::VertexArrayObject")
    , handle_(0)
    , attributes_(attributes)
    , vertex_buffer_(vertex_buffer)
    , index_buffer_(index_buffer)
{
    __create_vao();
}

gfx_gl_vertex_array_object::~gfx_gl_vertex_array_object()
{
    AEON_LOG_TRACE(logger_) << "Deleting Vertex Array Object (GL handle: " << handle_ << ")." << std::endl;
    glDeleteVertexArrays(1, &handle_);
    AEON_CHECK_GL_ERROR();
}

void gfx_gl_vertex_array_object::bind()
{
    if (!__is_valid())
    {
        AEON_LOG_TRACE(logger_) << "VAO not valid for this context, generating." << std::endl;
        __create_vao();
    }

    glBindVertexArray(handle_);
    AEON_CHECK_GL_ERROR();
}

bool gfx_gl_vertex_array_object::__is_valid() const
{
    return glIsVertexArray(handle_) == GL_TRUE;
}

void gfx_gl_vertex_array_object::__create_vao()
{
    vertex_buffer_->bind();
    index_buffer_->bind();

    glGenVertexArrays(1, &handle_);
    AEON_CHECK_GL_ERROR();

    AEON_LOG_TRACE(logger_) << "Created Vertex Array Object (GL handle: " << handle_ << ")." << std::endl;

    glBindVertexArray(handle_);
    AEON_CHECK_GL_ERROR();

    int attrib_index = 0;
    for (auto attribute : attributes_)
    {
        glEnableVertexAttribArray(attrib_index);
        AEON_CHECK_GL_ERROR();

        glVertexAttribPointer(attrib_index, attribute.size, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(attribute.stride),
                              reinterpret_cast<void *>(attribute.offset));
        AEON_CHECK_GL_ERROR();

        ++attrib_index;
    }
}

} // namespace gl
} // namespace gfx
} // namespace aeon
