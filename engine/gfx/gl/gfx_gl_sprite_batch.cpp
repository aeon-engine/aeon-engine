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

#include <gfx/gl/gfx_gl_sprite_batch.h>
#include <gfx/gl/gfx_gl_device.h>
#include <resources/atlas.h>
#include <gfx/gl_common/check_gl_error.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

gfx_gl_sprite_batch::gfx_gl_sprite_batch(gfx_gl_device *device, material_ptr material, std::uint16_t sprites_per_buffer)
    : gfx::sprite_batch(material, sprites_per_buffer)
    , logger_(common::logger::get_singleton(), "Gfx::GL::SpriteBatch")
    , sprite_count_(0)
{
    vertex_buffer_ = device->get_buffer_manager().create_buffer(buffer_type::array);
    index_buffer_ = device->get_buffer_manager().create_buffer(buffer_type::element_array);

    vertex_buffer_->set_data(0, nullptr, gfx::buffer_usage::stream_usage);

    __setup_index_buffer();
    __create_and_setup_vao();
}

void gfx_gl_sprite_batch::upload_sprite_buffer(const sprite_vertex *sprite_vertex_data, int count)
{
    if (count > sprites_per_buffer_)
    {
        AEON_LOG_ERROR(logger_) << "Sprite count exceeds buffersize (Given: " << count
                                << ", Max: " << sprites_per_buffer_ << ")." << std::endl;
        throw gfx_sprite_batch_full_exception();
    }

    int vertex_buffer_size = count * sizeof(gfx::sprite_vertex) * vertices_per_sprite;
    vertex_buffer_->set_data(vertex_buffer_size, sprite_vertex_data, gfx::buffer_usage::stream_usage);

    sprite_count_ = count;
}

void gfx_gl_sprite_batch::render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model)
{
    if (sprite_count_ == 0)
        return;

    material_->bind();

    vertex_buffer_->bind();
    index_buffer_->bind();

    material_->get_shader()->set_projection_matrix(projection);
    material_->get_shader()->set_model_matrix(model);
    material_->get_shader()->set_view_matrix(view);

    vao_->bind();

    GLuint element_size = static_cast<GLuint>(sprite_count_ * indices_per_sprite);
    glDrawRangeElements(GL_TRIANGLES, 0, element_size, element_size, GL_UNSIGNED_SHORT, nullptr);
    AEON_CHECK_GL_ERROR();
}

void gfx_gl_sprite_batch::__setup_index_buffer() const
{
    std::vector<uint16_t> index_buffer_data(sprites_per_buffer_ * indices_per_sprite);
    uint16_t *index_buffer_data_ptr = index_buffer_data.data();

    std::uint16_t offset = 0;
    for (std::uint16_t i = 0; i < sprites_per_buffer_; ++i)
    {
        std::uint16_t index_offset = i * vertices_per_sprite;
        index_buffer_data_ptr[offset++] = index_offset;
        index_buffer_data_ptr[offset++] = index_offset + 1;
        index_buffer_data_ptr[offset++] = index_offset + 2;
        index_buffer_data_ptr[offset++] = index_offset + 2;
        index_buffer_data_ptr[offset++] = index_offset + 1;
        index_buffer_data_ptr[offset++] = index_offset + 3;
    }

    int buffer_size = static_cast<int>(index_buffer_data.size() * sizeof(uint16_t));
    index_buffer_->set_data(buffer_size, index_buffer_data.data(), gfx::buffer_usage::static_usage);
}

void gfx_gl_sprite_batch::__create_and_setup_vao()
{
    vertex_attributes attributes = {
        vertex_attribute{2, sizeof(sprite_vertex), 0},  vertex_attribute{2, sizeof(sprite_vertex), 8},
        vertex_attribute{4, sizeof(sprite_vertex), 16}, vertex_attribute{4, sizeof(sprite_vertex), 32},
        vertex_attribute{4, sizeof(sprite_vertex), 48}, vertex_attribute{4, sizeof(sprite_vertex), 64},
        vertex_attribute{4, sizeof(sprite_vertex), 80},
    };

    vao_ = std::make_unique<gfx_gl_vertex_array_object>(attributes);
}

} // namespace gl
} // namespace gfx
} // namespace aeon
