/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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

#include <memory>
#include <gfx/gl/gfx_gl_texture_manager.h>
#include <gfx/gl/gfx_gl_shader_manager.h>
#include <gfx/gl/gfx_gl_device.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

device::device()
{
    texture_manager_ = std::make_shared<gl::texture_manager>();
    shader_manager_ = std::make_shared<gl::shader_manager>();
}

device::~device()
{
}

} // namespace gl
} // namespace gfx
} // namespace aeon
