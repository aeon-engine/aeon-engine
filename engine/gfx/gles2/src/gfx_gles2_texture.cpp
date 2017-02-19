/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#include <aeon/gfx/gles2/gfx_gles2_texture.h>
#include <aeon/gfx/gl_common/check_gl_error.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

gfx_gles2_texture::gfx_gles2_texture()
    : gfx::texture()
    , logger_(common::logger::get_singleton(), "Gfx::Gles2::Texture")
    , handle_(0)
    , size_(0)
    , pixel_format_(data::image::pixel_format::rgb)
{
}

gfx_gles2_texture::~gfx_gles2_texture()
{
    AEON_LOG_TRACE(logger_) << "Deleting Texture (GL handle: " << handle_ << ")." << std::endl;
    glDeleteTextures(1, &handle_);
    AEON_CHECK_GL_ERROR();
}

void gfx_gles2_texture::bind() const
{
    assert(glIsTexture(handle_) == GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, handle_);
    AEON_CHECK_GL_ERROR();
}

glm::vec2 gfx_gles2_texture::get_size() const
{
    return size_;
}

data::image::pixel_format gfx_gles2_texture::get_pixel_format() const
{
    return pixel_format_;
}

void gfx_gles2_texture::set_texture_bind_point(const int bind_point) const
{
    glActiveTexture(GL_TEXTURE0 + bind_point);
    AEON_CHECK_GL_ERROR();
}

} // namespace gles2
} // namespace gfx
} // namespace aeon
