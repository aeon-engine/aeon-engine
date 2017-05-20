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

#include <GL/glew.h>
#include <aeon/gfx/gfx_material.h>
#include <aeon/gfx/gl/gfx_gl_shader.h>
#include <aeon/gfx/gl/gfx_gl_texture.h>
#include <map>
#include <memory>

namespace aeon
{
namespace gfx
{
namespace gl
{

class gfx_gl_texture_handle_pair
{
public:
    explicit gfx_gl_texture_handle_pair(const GLint handle, gfx_gl_texture *texture)
        : handle_(handle)
        , texture_(texture)
    {
    }

    auto get_handle() const
    {
        return handle_;
    }

    auto get_texture() const
    {
        return texture_;
    }

private:
    GLint handle_;
    gfx_gl_texture *texture_;
};

class gfx_gl_material : public gfx::material
{
    friend class gfx_gl_material_manager;

    void bind() override;

public:
    explicit gfx_gl_material(const std::shared_ptr<shader> &shader,
                             const std::map<std::string, std::shared_ptr<texture>> &samplers);
    virtual ~gfx_gl_material() = default;

    auto get_shader() const -> gfx::shader * override;
    auto get_sampler(const std::string &name) const -> gfx::texture * override;
    auto get_sampler_by_index(const int index) const -> gfx::texture * override;

    bool sampler_has_alpha() const override;

protected:
    auto __convert_sampler_map_to_gl(const std::map<std::string, std::shared_ptr<texture>> &samplers) const
        -> std::map<std::string, std::shared_ptr<gfx_gl_texture>>;
    auto __generate_sampler_indices(const std::map<std::string, std::shared_ptr<gfx_gl_texture>> &samplers) const
        -> std::vector<gfx_gl_texture_handle_pair>;

    std::shared_ptr<gfx_gl_shader> shader_;
    std::map<std::string, std::shared_ptr<gfx_gl_texture>> sampler_map_;
    std::vector<gfx_gl_texture_handle_pair> samplers_;
    bool sampler_has_alpha_;
};

} // namespace gl
} // namespace gfx
} // namespace aeon
