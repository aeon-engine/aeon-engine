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

#pragma once

#include <GL/glew.h>
#include <aeon/gfx/gfx_material.h>
#include <aeon/gfx/gl/gfx_gl_shader.h>
#include <aeon/gfx/gl/gfx_gl_texture.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

class gfx_gl_material : public gfx::material
{
    friend class gfx_gl_material_manager;

    void bind() override;

public:
    explicit gfx_gl_material(const std::shared_ptr<shader> &shader, const material::sampler_map &samplers);
    virtual ~gfx_gl_material() = default;

    gfx::shader *get_shader() const override;
    gfx::texture *get_sampler(const std::string &name) const override;

protected:
    using gl_sampler_map = std::map<std::string, std::shared_ptr<gfx_gl_texture>>;
    using gl_samplers = std::vector<gfx_gl_texture *>;

    gl_sampler_map __convert_sampler_map_to_gl(const material::sampler_map &samplers) const;
    gl_samplers __generate_sampler_indices(const gl_sampler_map &samplers) const;

    std::shared_ptr<gfx_gl_shader> shader_;
    gl_sampler_map sampler_map_;
    gl_samplers samplers_;
};

} // namespace gl
} // namespace gfx
} // namespace aeon
