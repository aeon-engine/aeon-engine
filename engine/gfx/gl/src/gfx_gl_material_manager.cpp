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

#include <aeon/gfx/gl/gfx_gl_material_manager.h>
#include <aeon/gfx/gl/gfx_gl_material.h>
#include <aeon/gfx/gl/gfx_gl_device.h>
#include <aeon/data/material.h>
#include <GL/glew.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

material_ptr gfx_gl_material_manager::create(const shader_ptr &shader, const material::sampler_map &samplers)
{
    return std::make_shared<gfx_gl_material>(shader, samplers);
}

} // namespace gl
} // namespace gfx
} // namespace aeon