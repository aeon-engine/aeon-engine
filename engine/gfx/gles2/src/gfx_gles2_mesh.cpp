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

#include <aeon/gfx/gles2/gfx_gles2_mesh.h>
#include <aeon/gfx/gles2/gfx_gles2_device.h>
#include <aeon/gfx/gl_common/check_gl_error.h>
#include <cstddef>

namespace aeon
{
namespace gfx
{
namespace gles2
{

gfx_gles2_mesh::gfx_gles2_mesh(gfx_gles2_device *device, std::shared_ptr<material> material)
    : gfx::mesh()
    , logger_(common::logger::get_singleton(), "Gfx::GL::Mesh")
    , material_(material)
    , vertex_buffer_(device->get_buffer_manager().create_buffer(buffer_type::array))
    , index_buffer_(device->get_buffer_manager().create_buffer(buffer_type::element_array))
    , element_count_(0)
{
}

void gfx_gles2_mesh::upload_vertex_buffer(const std::vector<data::vertex_data> &vertex_data,
                                          const gfx::buffer_usage usage)
{
    int buffer_size = static_cast<int>(vertex_data.size() * sizeof(data::vertex_data));
    vertex_buffer_->set_data(buffer_size, vertex_data.data(), usage);
}

void gfx_gles2_mesh::upload_index_buffer(const std::vector<std::uint32_t> &index_data, const gfx::buffer_usage usage)
{
    // TODO: Handle this better. We can't do 32 bit indices on gles2.
    std::vector<std::uint16_t> index_data_short;
    for (auto &i : index_data)
    {
        index_data_short.push_back(static_cast<std::uint16_t>(i));
    }

    element_count_ = static_cast<GLuint>(index_data.size());
    index_buffer_->set_data(static_cast<int>(element_count_ * sizeof(std::uint16_t)), index_data_short.data(), usage);
}

void gfx_gles2_mesh::render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model)
{
    if (!vertex_buffer_ || !index_buffer_)
        return;

    material_->bind();
    material_->get_shader()->set_projection_matrix(projection);
    material_->get_shader()->set_model_matrix(model);
    material_->get_shader()->set_view_matrix(view);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(data::vertex_data),
    reinterpret_cast<GLvoid*>(offsetof(data::vertex_data, position)));
    AEON_CHECK_GL_ERROR();
    glEnableVertexAttribArray(0);
    AEON_CHECK_GL_ERROR();

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(data::vertex_data),
        reinterpret_cast<GLvoid*>(offsetof(data::vertex_data, normal)));
    AEON_CHECK_GL_ERROR();
    glEnableVertexAttribArray(1);
    AEON_CHECK_GL_ERROR();

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(data::vertex_data),
        reinterpret_cast<GLvoid*>(offsetof(data::vertex_data, uvw)));
    AEON_CHECK_GL_ERROR();
    glEnableVertexAttribArray(2);
    AEON_CHECK_GL_ERROR();

    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(data::vertex_data),
        reinterpret_cast<GLvoid*>(offsetof(data::vertex_data, color)));
    AEON_CHECK_GL_ERROR();
    glEnableVertexAttribArray(3);
    AEON_CHECK_GL_ERROR();

     glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(data::vertex_data),
        reinterpret_cast<GLvoid*>(offsetof(data::vertex_data, tangent)));
    AEON_CHECK_GL_ERROR();
    glEnableVertexAttribArray(4);
    AEON_CHECK_GL_ERROR();

    glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(data::vertex_data),
        reinterpret_cast<GLvoid*>(offsetof(data::vertex_data, bitangent)));
    AEON_CHECK_GL_ERROR();
    glEnableVertexAttribArray(5);
    AEON_CHECK_GL_ERROR();

    glDrawElements(GL_TRIANGLES, element_count_, GL_UNSIGNED_SHORT, nullptr);
    AEON_CHECK_GL_ERROR();
}

bool gfx_gles2_mesh::has_alpha() const
{
    return material_->sampler_has_alpha();
}

} // namespace gles2
} // namespace gfx
} // namespace aeon
