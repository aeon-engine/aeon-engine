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

#include <aeon/gfx/gles2/gfx_gles2_material.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

gfx_gles2_material::gfx_gles2_material(const std::shared_ptr<shader> &shader,
                                       const std::map<std::string, std::shared_ptr<texture>> &samplers)
    : shader_(std::dynamic_pointer_cast<gfx_gles2_shader>(shader))
    , sampler_map_(__convert_sampler_map_to_gl(samplers))
    , samplers_(__generate_sampler_indices(sampler_map_))
    , sampler_has_alpha_(false)
{
    for (auto &sampler : samplers)
    {
        if (sampler.second->get_pixel_format() == data::image::pixel_format::rgba)
        {
            sampler_has_alpha_ = true;
            break;
        }
    }
}

void gfx_gles2_material::bind()
{
    shader_->bind();

    int bind_point = 0;
    for (auto &sampler : samplers_)
    {
        auto texture = sampler.get_texture();
        texture->set_texture_bind_point(bind_point);
        texture->bind();
        shader_->bind_sampler(sampler.get_handle(), bind_point);
        ++bind_point;
    }
}

auto gfx_gles2_material::get_shader() const -> gfx::shader *
{
    return shader_.get();
}

auto gfx_gles2_material::get_sampler(const std::string &name) const -> gfx::texture *
{
    auto result = sampler_map_.find(name);

    if (result == sampler_map_.end())
        throw gfx_material_exception();

    return result->second.get();
}

bool gfx_gles2_material::sampler_has_alpha() const
{
    return sampler_has_alpha_;
}

auto gfx_gles2_material::__convert_sampler_map_to_gl(const std::map<std::string, std::shared_ptr<texture>> &samplers)
    const -> std::map<std::string, std::shared_ptr<gfx_gles2_texture>>
{
    auto gl_samplers = std::map<std::string, std::shared_ptr<gfx_gles2_texture>>();

    for (auto &sampler : samplers)
    {
        gl_samplers[sampler.first] = std::dynamic_pointer_cast<gfx_gles2_texture>(sampler.second);
    }

    return gl_samplers;
}

auto gfx_gles2_material::__generate_sampler_indices(
    const std::map<std::string, std::shared_ptr<gfx_gles2_texture>> &samplers) const
    -> std::vector<gfx_gles2_texture_handle_pair>
{
    auto gl_samplers = std::vector<gfx_gles2_texture_handle_pair>();

    for (auto &sampler : samplers)
    {
        auto sampler_name = sampler.first;
        auto gl_texture_ptr = sampler.second.get();

        auto sampler_handle = shader_->get_sampler_handle_by_name(sampler_name);

        gl_samplers.push_back(gfx_gles2_texture_handle_pair(sampler_handle, gl_texture_ptr));
    }

    return gl_samplers;
}

} // namespace gles2
} // namespace gfx
} // namespace aeon
