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

#include <aeon/gfx/gfx_texture.h>
#include <aeon/common/logger.h>
#include <aeon/gfx/gfx_buffer.h>
#include <GL/glew.h>
#include <vector>
#include <memory>

namespace aeon
{
namespace gfx
{
namespace gl
{

struct vertex_attribute
{
    explicit vertex_attribute(unsigned int size_, unsigned int stride_, unsigned int offset_)
        : size(size_)
        , stride(stride_)
        , offset(offset_)
    {
    }

    unsigned int size;
    size_t stride;
    size_t offset;
};

using vertex_attributes = std::vector<vertex_attribute>;

class gfx_gl_vertex_array_object
{
public:
    explicit gfx_gl_vertex_array_object(const vertex_attributes &attributes, std::shared_ptr<buffer> vertex_buffer,
                                        std::shared_ptr<buffer> index_buffer);
    ~gfx_gl_vertex_array_object();

    void bind();

private:
    auto __is_valid() const -> bool;
    void __create_vao();

    logger::logger logger_;
    GLuint handle_;
    vertex_attributes attributes_;
    std::shared_ptr<buffer> vertex_buffer_;
    std::shared_ptr<buffer> index_buffer_;
};

} // namespace gl
} // namespace gfx
} // namespace aeon
