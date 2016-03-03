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

#include <gfx/gles2/gfx_gles2_texture.h>
#include <gfx/gles2/gfx_gles2_shader.h>
#include <common/check_gl_error.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

texture::texture(resources::image_ptr image)
    : gfx::texture(image)
    , logger_(common::logger::get_singleton(), "Gfx::GL::Texture")
    , handle_(0)
{
}

texture::~texture()
{
    AEON_LOG_TRACE(logger_) << "Deleting Texture (GL handle: " << handle_ << ")." << std::endl;
    glDeleteTextures(1, &handle_);
    AEON_CHECK_GL_ERROR();
}

void texture::bind(shader &s) const
{
    glActiveTexture(GL_TEXTURE0);
    AEON_CHECK_GL_ERROR();

    glBindTexture(GL_TEXTURE_2D, handle_);
    AEON_CHECK_GL_ERROR();

    glUniform1i(s.get_texture0_handle(), 0);
    AEON_CHECK_GL_ERROR();
}

} // namespace gles2
} // namespace gfx
} // namespace aeon
