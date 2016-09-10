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

#pragma once

#include <gfx/gl/gfx_gl_mesh.h>
#include <gfx/gl/gfx_gl_device.h>
#include <gfx/gl_common/check_gl_error.h>
#include <cstddef>

namespace aeon
{
namespace gfx
{
namespace gl
{

gfx_gl_mesh::gfx_gl_mesh(gfx_gl_device *device, material_ptr material)
    : gfx::mesh()
    , logger_(common::logger::get_singleton(), "Gfx::GL::Mesh")
    , material_(material)
    , vertex_buffer_(device->get_buffer_manager().create_buffer(buffer_type::array))
    , index_buffer_(device->get_buffer_manager().create_buffer(buffer_type::element_array))
    , element_count_(0)
    , vao_()
{
    __create_and_setup_vao();
}

void gfx_gl_mesh::upload_vertex_buffer(const std::vector<mesh_vertex> &vertex_data, const gfx::buffer_usage usage)
{
    int buffer_size = static_cast<int>(vertex_data.size() * sizeof(gfx::mesh_vertex));
    vertex_buffer_->set_data(buffer_size, vertex_data.data(), usage);

    __check_vao();
}

void gfx_gl_mesh::upload_index_buffer(const std::vector<std::uint16_t> &index_data, const gfx::buffer_usage usage)
{
    element_count_ = static_cast<GLuint>(index_data.size());
    index_buffer_->set_data(static_cast<int>(element_count_ * sizeof(uint16_t)), index_data.data(), usage);

    __check_vao();
}

void gfx_gl_mesh::render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model)
{
    if (!vertex_buffer_ || ! index_buffer_)
        return;

    material_->bind();

    vertex_buffer_->bind();
    index_buffer_->bind();

    material_->get_shader()->set_projection_matrix(projection);
    material_->get_shader()->set_model_matrix(model);
    material_->get_shader()->set_view_matrix(view);

    vao_->bind();

    glDrawRangeElements(GL_TRIANGLES, 0, element_count_, element_count_, GL_UNSIGNED_SHORT, nullptr);
    AEON_CHECK_GL_ERROR();
}

void gfx_gl_mesh::__check_vao()
{
    if (index_buffer_->has_data() && vertex_buffer_->has_data() && !vao_)
        __create_and_setup_vao();
}

void gfx_gl_mesh::__create_and_setup_vao()
{
    vertex_buffer_->bind();
    index_buffer_->bind();

    vertex_attributes attributes = {
        vertex_attribute{ 3, sizeof(mesh_vertex), offsetof(mesh_vertex, x) }, // X Y Z
        vertex_attribute{ 2, sizeof(mesh_vertex), offsetof(mesh_vertex, u) }, // U V
        vertex_attribute{ 4, sizeof(mesh_vertex), offsetof(mesh_vertex, r) }, // R G B A
    };

    vao_ = std::make_unique<gfx_gl_vertex_array_object>(attributes);
}

} // namespace gl
} // namespace gfx
} // namespace aeon
