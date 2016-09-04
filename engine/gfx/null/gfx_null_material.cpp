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

#include <gfx/null/gfx_null_material.h>

namespace aeon
{
namespace gfx
{
namespace null
{

void gfx_null_material::bind()
{
    shader_->bind();
    texture_->bind();
}

gfx::shader *gfx_null_material::get_shader() const
{
    return shader_.get();
}

gfx::texture *gfx_null_material::get_texture() const
{
    return texture_.get();
}

} // namespace null
} // namespace gfx
} // namespace aeon
