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

#include <gfx/gfx_mesh.h>
#include <gfx/gles2/gfx_gles2_buffer.h>
#include <gfx/gfx_material.h>
#include <common/logger.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

class gfx_gles2_device;
class gfx_gles2_mesh : public gfx::mesh
{
public:
    explicit gfx_gles2_mesh(gfx_gles2_device *device, gfx::material_ptr material);
    virtual ~gfx_gles2_mesh() = default;

    void upload_vertex_buffer(const std::vector<data::vertex_data> &vertex_data,
        const gfx::buffer_usage usage) override;
    void upload_index_buffer(const std::vector<std::uint16_t> &index_data, const gfx::buffer_usage usage) override;

    void render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model) override;

private:
    aeon::logger::logger logger_;

    gfx::material_ptr material_;

    gfx::buffer_ptr vertex_buffer_;
    gfx::buffer_ptr index_buffer_;
    GLuint element_count_;
};

} // namespace gles2
} // namespace gfx
} // namespace aeon
