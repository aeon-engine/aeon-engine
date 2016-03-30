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

#include <GL/glew.h>
#include <gfx/gfx_material.h>
#include <gfx/gl/gfx_gl_shader.h>
#include <gfx/gl/gfx_gl_texture.h>

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
    gfx_gl_material() = default;
    ~gfx_gl_material() = default;

    gfx::shader *get_shader() const override;
    gfx::texture *get_texture() const override;

protected:
    gl::shader_gl_ptr shader_;
    gl::gfx_gl_texture_ptr texture_;
};

using material_gl_ptr = std::shared_ptr<gfx_gl_material>;

} // namespace gl
} // namespace gfx
} // namespace aeon
