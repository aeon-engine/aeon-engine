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

#include <aeon/gfx/gl/gfx_gl_material.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

gfx_gl_material::gfx_gl_material(const std::shared_ptr<shader> &shader, const material::sampler_map &samplers)
    : shader_(std::dynamic_pointer_cast<gfx_gl_shader>(shader))
    , sampler_map_(std::move(__convert_sampler_map_to_gl(samplers)))
    , samplers_(std::move(__generate_sampler_indices(sampler_map_)))
{
}

void gfx_gl_material::bind()
{
    // TODO: bind all samplers
    shader_->bind();
    samplers_[0]->bind();
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

gfx_gl_material::gl_sampler_map
gfx_gl_material::__convert_sampler_map_to_gl(const material::sampler_map &samplers) const
{
    gfx_gl_material::gl_sampler_map gl_samplers;

    for (auto &sampler : samplers)
    {
        gl_samplers[sampler.first] = std::dynamic_pointer_cast<gfx_gl_texture>(sampler.second);
    }

    return std::move(gl_samplers);
}

gfx_gl_material::gl_samplers
gfx_gl_material::__generate_sampler_indices(const gfx_gl_material::gl_sampler_map &samplers) const
{
    gfx_gl_material::gl_samplers gl_samplers;

    // TODO: Sampler index info should be generated based on the shader and the material definition.
    gl_samplers.push_back(samplers.at("texture").get());

    return std::move(gl_samplers);
}

} // namespace gl
} // namespace gfx
} // namespace aeon
