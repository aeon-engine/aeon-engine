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
