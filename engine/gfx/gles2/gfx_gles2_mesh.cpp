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

void gfx_gles2_mesh::upload_vertex_buffer(const std::vector<mesh_vertex> &vertex_data, const gfx::buffer_usage usage)
{
    int buffer_size = static_cast<int>(vertex_data.size() * sizeof(gfx::mesh_vertex));
    vertex_buffer_->set_data(buffer_size, vertex_data.data(), usage);
}

void gfx_gles2_mesh::upload_index_buffer(const std::vector<std::uint16_t> &index_data, const gfx::buffer_usage usage)
{
    element_count_ = static_cast<GLuint>(index_data.size());
    index_buffer_->set_data(static_cast<int>(index_data.size() * sizeof(std::uint16_t)), index_data.data(), usage);
}

void gfx_gles2_mesh::render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model)
{
    if (!vertex_buffer_ || ! index_buffer_)
        return;

    material_->bind();

    vertex_buffer_->bind();
    index_buffer_->bind();

    material_->get_shader()->set_projection_matrix(projection);
    material_->get_shader()->set_model_matrix(model);
    material_->get_shader()->set_view_matrix(view);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(mesh_vertex), (GLvoid *) 0); //offsetof(mesh_vertex, x));
    AEON_CHECK_GL_ERROR();
    glEnableVertexAttribArray(0);
    AEON_CHECK_GL_ERROR();

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(mesh_vertex), (GLvoid *) 12); //offsetof(mesh_vertex, u));
    AEON_CHECK_GL_ERROR();
    glEnableVertexAttribArray(1);
    AEON_CHECK_GL_ERROR();

    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(mesh_vertex), (GLvoid *) 20); //offsetof(mesh_vertex, r));
    AEON_CHECK_GL_ERROR();
    glEnableVertexAttribArray(2);
    AEON_CHECK_GL_ERROR();

    glDrawElements(GL_TRIANGLES, element_count_, GL_UNSIGNED_SHORT, nullptr);
}

} // namespace gles2
} // namespace gfx
} // namespace aeon
