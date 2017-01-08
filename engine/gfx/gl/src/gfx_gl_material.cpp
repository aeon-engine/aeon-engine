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

#include <aeon/gfx/gl/gfx_gl_material.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

gfx_gl_material::gfx_gl_material(const std::shared_ptr<shader> &shader,
                                 const std::map<std::string, std::shared_ptr<texture>> &samplers)
    : shader_(std::dynamic_pointer_cast<gfx_gl_shader>(shader))
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

void gfx_gl_material::bind()
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

gfx::shader *gfx_gl_material::get_shader() const
{
    return shader_.get();
}

gfx::texture *gfx_gl_material::get_sampler(const std::string &name) const
{
    auto result = sampler_map_.find(name);

    if (result == sampler_map_.end())
        throw gfx_material_exception();

    return result->second.get();
}

bool gfx_gl_material::sampler_has_alpha() const
{
    return sampler_has_alpha_;
}

auto gfx_gl_material::__convert_sampler_map_to_gl(const std::map<std::string, std::shared_ptr<texture>> &samplers) const
    -> std::map<std::string, std::shared_ptr<gfx_gl_texture>>
{
    auto gl_samplers = std::map<std::string, std::shared_ptr<gfx_gl_texture>>();

    for (auto &sampler : samplers)
    {
        gl_samplers[sampler.first] = std::dynamic_pointer_cast<gfx_gl_texture>(sampler.second);
    }

    return gl_samplers;
}

auto gfx_gl_material::__generate_sampler_indices(const std::map<std::string, std::shared_ptr<gfx_gl_texture>> &samplers)
    const -> std::vector<gfx_gl_texture_handle_pair>
{
    auto gl_samplers = std::vector<gfx_gl_texture_handle_pair>();

    for (auto &sampler : samplers)
    {
        auto sampler_name = sampler.first;
        auto gl_texture_ptr = sampler.second.get();

        auto sampler_handle = shader_->get_sampler_handle_by_name(sampler_name);

        gl_samplers.push_back(gfx_gl_texture_handle_pair(sampler_handle, gl_texture_ptr));
    }

    return gl_samplers;
}

} // namespace gl
} // namespace gfx
} // namespace aeon
