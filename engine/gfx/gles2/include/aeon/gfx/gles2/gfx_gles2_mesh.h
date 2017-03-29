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

#include <aeon/gfx/gfx_mesh.h>
#include <aeon/gfx/gles2/gfx_gles2_buffer.h>
#include <aeon/gfx/gfx_material.h>
#include <aeon/common/logger.h>

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
    explicit gfx_gles2_mesh(gfx_gles2_device *device, std::shared_ptr<material> material);
    virtual ~gfx_gles2_mesh() = default;

    void upload_vertex_buffer(const std::vector<data::vertex_data> &vertex_data,
                              const gfx::buffer_usage usage) override;
    void upload_index_buffer(const std::vector<std::uint32_t> &index_data, const gfx::buffer_usage usage) override;

    void render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model) override;

    auto has_alpha() const -> bool override;

private:
    void __check_vao() const;
    void __create_and_setup_vao();

    aeon::logger::logger logger_;

    std::shared_ptr<material> material_;

    std::shared_ptr<buffer> vertex_buffer_;
    std::shared_ptr<buffer> index_buffer_;
    GLuint element_count_;
};

} // namespace gles2
} // namespace gfx
} // namespace aeon
