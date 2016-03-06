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

#include <build_config.h>

#ifdef AEON_PLATFORM_IOS
#include <OpenGLES/ES2/gl.h>
#else
#include <GLES2/gl2.h>
#endif // AEON_PLATFORM_IOS

#include <gfx/gfx_material.h>
#include <gfx/gles2/gfx_gles2_shader.h>
#include <gfx/gles2/gfx_gles2_texture.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

class material : public gfx::material
{
    friend class material_manager;

    void bind() override;

public:
    material() = default;
    ~material() = default;

    gfx::shader *get_shader() const override;
    gfx::texture *get_texture() const override;

protected:
    gles2::shader_gles2_ptr shader_;
    gles2::texture_gles2_ptr texture_;
};

using material_gl_ptr = std::shared_ptr<material>;

} // namespace gles2
} // namespace gfx
} // namespace aeon
