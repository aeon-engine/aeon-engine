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

#include <aeon/gfx/gfx_material.h>
#include <aeon/gfx/gles2/gfx_gles2_shader.h>
#include <aeon/gfx/gles2/gfx_gles2_texture.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

class gfx_gles2_texture_handle_pair
{
public:
    explicit gfx_gles2_texture_handle_pair(const GLint handle, gfx_gles2_texture *texture)
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
    gfx_gles2_texture *texture_;
};

class gfx_gles2_material : public gfx::material
{
    friend class gfx_gles2_material_manager;

    void bind() override;

public:
    explicit gfx_gles2_material(const std::shared_ptr<shader> &shader,
                             const std::map<std::string, std::shared_ptr<texture>> &samplers);
    virtual ~gfx_gles2_material() = default;

    gfx::shader *get_shader() const override;
    gfx::texture *get_sampler(const std::string &name) const override;

    bool sampler_has_alpha() const override;

protected:
    auto __convert_sampler_map_to_gl(const std::map<std::string, std::shared_ptr<texture>> &samplers) const
        -> std::map<std::string, std::shared_ptr<gfx_gles2_texture>>;
    auto __generate_sampler_indices(const std::map<std::string, std::shared_ptr<gfx_gles2_texture>> &samplers) const
        -> std::vector<gfx_gles2_texture_handle_pair>;

    std::shared_ptr<gfx_gles2_shader> shader_;
    std::map<std::string, std::shared_ptr<gfx_gles2_texture>> sampler_map_;
    std::vector<gfx_gles2_texture_handle_pair> samplers_;
    bool sampler_has_alpha_;
};

} // namespace gles2
} // namespace gfx
} // namespace aeon
