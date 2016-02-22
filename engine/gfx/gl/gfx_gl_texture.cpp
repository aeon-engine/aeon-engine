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

#include <gfx/gl/gfx_gl_texture.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

texture::texture(resources::image_ptr image)
    : gfx::texture(image)
    , handle_(0)
{
}

texture::~texture()
{
    glDeleteTextures(1, &handle_);
}

void texture::bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, handle_);
    glBindSampler(0, 1);
}

} // namespace gl
} // namespace gfx
} // namespace aeon
