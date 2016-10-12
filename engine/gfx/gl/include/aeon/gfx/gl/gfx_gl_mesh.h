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

#include <aeon/gfx/gfx_mesh.h>
#include <aeon/gfx/gl/gfx_gl_buffer.h>
#include <aeon/gfx/gfx_material.h>
#include <aeon/gfx/gl/gfx_gl_vertex_array_object.h>
#include <aeon/common/logger.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

class gfx_gl_device;
class gfx_gl_mesh : public gfx::mesh
{
public:
    explicit gfx_gl_mesh(gfx_gl_device *device, material_ptr material);
    virtual ~gfx_gl_mesh() = default;

    void upload_vertex_buffer(const std::vector<data::vertex_data> &vertex_data,
                              const gfx::buffer_usage usage) override;
    void upload_index_buffer(const std::vector<std::uint16_t> &index_data, const gfx::buffer_usage usage) override;

    void render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model) override;

private:
    void __check_vao();
    void __create_and_setup_vao();

    aeon::logger::logger logger_;

    gfx::material_ptr material_;

    gfx::buffer_ptr vertex_buffer_;
    gfx::buffer_ptr index_buffer_;
    GLuint element_count_;
    vertex_array_object_ptr vao_;
};

} // namespace gl
} // namespace gfx
} // namespace aeon
