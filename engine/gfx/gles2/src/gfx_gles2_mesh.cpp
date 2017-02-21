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

#include <gfx/gles2/gfx_gles2_mesh.h>
#include <gfx/gles2/gfx_gles2_device.h>
#include <gfx/gl_common/check_gl_error.h>
#include <cstddef>

namespace aeon
{
namespace gfx
{
namespace gles2
{

gfx_gles2_mesh::gfx_gles2_mesh(gfx_gles2_device *device, material_ptr material)
    : gfx::mesh()
    , logger_(common::logger::get_singleton(), "Gfx::GLES2::Mesh")
    , material_(material)
    , vertex_buffer_(device->get_buffer_manager().create_buffer(buffer_type::array))
    , index_buffer_(device->get_buffer_manager().create_buffer(buffer_type::element_array))
    , element_count_(0)
{
    vertex_buffer_->set_data(0, nullptr, gfx::buffer_usage::stream_usage);
}

void gfx_gles2_mesh::upload_vertex_buffer(const std::vector<data::vertex_data> &vertex_data,
                                          const gfx::buffer_usage usage)
{
    int buffer_size = static_cast<int>(vertex_data.size() * sizeof(data::vertex_data));
    vertex_buffer_->set_data(buffer_size, vertex_data.data(), usage);
}

void gfx_gles2_mesh::upload_index_buffer(const std::vector<std::uint16_t> &index_data, const gfx::buffer_usage usage)
{
    element_count_ = static_cast<GLuint>(index_data.size());
    index_buffer_->set_data(static_cast<int>(index_data.size() * sizeof(std::uint16_t)), index_data.data(), usage);
}

void gfx_gles2_mesh::render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model)
{
    if (!vertex_buffer_ || !index_buffer_)
        return;

    material_->bind();

    vertex_buffer_->bind();
    index_buffer_->bind();

    material_->get_shader()->set_projection_matrix(projection);
    material_->get_shader()->set_model_matrix(model);
    material_->get_shader()->set_view_matrix(view);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(data::vertex_data),
                          reinterpret_cast<GLvoid *>(offsetof(data::vertex_data, position)));
    AEON_CHECK_GL_ERROR();
    glEnableVertexAttribArray(0);
    AEON_CHECK_GL_ERROR();

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(data::vertex_data),
                          reinterpret_cast<GLvoid *>(offsetof(data::vertex_data, normal)));
    AEON_CHECK_GL_ERROR();
    glEnableVertexAttribArray(1);
    AEON_CHECK_GL_ERROR();

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(data::vertex_data),
                          reinterpret_cast<GLvoid *>(offsetof(data::vertex_data, uvw)));
    AEON_CHECK_GL_ERROR();
    glEnableVertexAttribArray(2);
    AEON_CHECK_GL_ERROR();

    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(data::vertex_data),
                          reinterpret_cast<GLvoid *>(offsetof(data::vertex_data, color)));
    AEON_CHECK_GL_ERROR();
    glEnableVertexAttribArray(3);
    AEON_CHECK_GL_ERROR();

    glDrawElements(GL_TRIANGLES, element_count_, GL_UNSIGNED_SHORT, nullptr);
}

} // namespace gles2
} // namespace gfx
} // namespace aeon
