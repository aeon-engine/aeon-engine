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
#include <gfx/gl_common/check_gl_error.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

gfx_gl_texture::gfx_gl_texture(const resources::image &image)
    : gfx::texture(image)
    , logger_(common::logger::get_singleton(), "Gfx::GL::Texture")
    , handle_(0)
{
}

gfx_gl_texture::~gfx_gl_texture()
{
    AEON_LOG_TRACE(logger_) << "Deleting Texture (GL handle: " << handle_ << ")." << std::endl;
    glDeleteTextures(1, &handle_);
    AEON_CHECK_GL_ERROR();
}

void gfx_gl_texture::bind() const
{
    glActiveTexture(GL_TEXTURE0);
    AEON_CHECK_GL_ERROR();

    glBindTexture(GL_TEXTURE_2D, handle_);
    AEON_CHECK_GL_ERROR();
}

} // namespace gl
} // namespace gfx
} // namespace aeon
