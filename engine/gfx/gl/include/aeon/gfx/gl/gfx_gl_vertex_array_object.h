/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#include <aeon/gfx/gfx_texture.h>
#include <aeon/common/logger.h>
#include <aeon/gfx/gfx_buffer.h>
#include <GL/glew.h>
#include <vector>

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
    bool __is_valid() const;
    void __create_vao();

    aeon::logger::logger logger_;
    GLuint handle_;
    vertex_attributes attributes_;
    std::shared_ptr<buffer> vertex_buffer_;
    std::shared_ptr<buffer> index_buffer_;
};

} // namespace gl
} // namespace gfx
} // namespace aeon
