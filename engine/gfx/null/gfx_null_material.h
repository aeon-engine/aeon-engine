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

#include <gfx/gfx_material.h>
#include <gfx/null/gfx_null_shader.h>
#include <gfx/null/gfx_null_texture.h>

namespace aeon
{
namespace gfx
{
namespace null
{

class gfx_null_material : public gfx::material
{
    friend class gfx_null_material_manager;

    void bind() override;

public:
    gfx_null_material() = default;
    ~gfx_null_material() = default;

    gfx::shader *get_shader() const override;
    gfx::texture *get_texture() const override;

protected:
    gfx_null_shader_ptr shader_;
    gfx_null_texture_ptr texture_;
};

using material_null_ptr = std::shared_ptr<gfx_null_material>;

} // namespace null
} // namespace gfx
} // namespace aeon
