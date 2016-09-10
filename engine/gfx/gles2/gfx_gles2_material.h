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

#include <GLES2/gl2.h>
#include <gfx/gfx_material.h>
#include <gfx/gles2/gfx_gles2_shader.h>
#include <gfx/gles2/gfx_gles2_texture.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

class gfx_gles2_material : public gfx::material
{
    friend class gfx_gles2_material_manager;

    void bind() override;

public:
    gfx_gles2_material() = default;
    ~gfx_gles2_material() = default;

    gfx::shader *get_shader() const override;
    gfx::texture *get_texture() const override;

protected:
    gfx_gles2_shader_ptr shader_;
    gfx_gles2_texture_ptr texture_;
};

using gfx_gles2_material_ptr = std::shared_ptr<gfx_gles2_material>;

} // namespace gles2
} // namespace gfx
} // namespace aeon
