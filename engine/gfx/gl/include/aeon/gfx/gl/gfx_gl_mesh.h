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
    explicit gfx_gl_mesh(gfx_gl_device *device, std::shared_ptr<material> material);
    virtual ~gfx_gl_mesh() = default;

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
    std::unique_ptr<gfx_gl_vertex_array_object> vao_;
};

} // namespace gl
} // namespace gfx
} // namespace aeon
