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

#include <gfx/gles2/gfx_gles2_sprite_batch.h>
#include <gfx/gles2/gfx_gles2_device.h>
#include <resources/atlas.h>
#include <gfx/gl_common/check_gl_error.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

sprite_batch::sprite_batch(device *device, material_ptr material, std::uint16_t sprites_per_buffer)
    : gfx::sprite_batch(material, sprites_per_buffer)
    , logger_(common::logger::get_singleton(), "Gfx::GL::SpriteBatch")
    , sprite_count_(0)
{
    vertex_buffer_ = device->get_buffer_manager().create_buffer(buffer_type::array);
    index_buffer_ = device->get_buffer_manager().create_buffer(buffer_type::element_array);

    vertex_buffer_->set_data(0, nullptr, gfx::buffer_usage::stream_usage);

    __setup_index_buffer();
}

void sprite_batch::upload_sprite_buffer(const sprite_vertex *sprite_vertex_data, int count)
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

void sprite_batch::render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model)
{
    if (sprite_count_ == 0)
        return;

    material_->bind();

    vertex_buffer_->bind();
    index_buffer_->bind();

    material_->get_shader()->set_projection_matrix(projection);
    material_->get_shader()->set_model_matrix(model);
    material_->get_shader()->set_view_matrix(view);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex), (GLvoid *) 0);
    AEON_CHECK_GL_ERROR();
	glEnableVertexAttribArray(0);
    AEON_CHECK_GL_ERROR();

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex), (GLvoid *) 8);
    AEON_CHECK_GL_ERROR();
	glEnableVertexAttribArray(1);
    AEON_CHECK_GL_ERROR();

    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex), (GLvoid *) 16);
    AEON_CHECK_GL_ERROR();
	glEnableVertexAttribArray(2);
    AEON_CHECK_GL_ERROR();

    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex), (GLvoid *) 32);
    AEON_CHECK_GL_ERROR();
	glEnableVertexAttribArray(3);
    AEON_CHECK_GL_ERROR();

    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex), (GLvoid *) 48);
    AEON_CHECK_GL_ERROR();
	glEnableVertexAttribArray(4);
    AEON_CHECK_GL_ERROR();

    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex), (GLvoid *) 64);
    AEON_CHECK_GL_ERROR();
	glEnableVertexAttribArray(5);
    AEON_CHECK_GL_ERROR();

    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(sprite_vertex), (GLvoid *) 80);
    AEON_CHECK_GL_ERROR();
	glEnableVertexAttribArray(6);
    AEON_CHECK_GL_ERROR();

    GLuint element_size = static_cast<GLuint>(sprite_count_ * indices_per_sprite);
    glDrawElements(GL_TRIANGLES, element_size, GL_UNSIGNED_SHORT, nullptr);
}

void sprite_batch::__setup_index_buffer() const
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

} // namespace gles2
} // namespace gfx
} // namespace aeon
