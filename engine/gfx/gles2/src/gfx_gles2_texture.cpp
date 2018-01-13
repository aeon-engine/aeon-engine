/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
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

auto gfx_gles2_texture::get_size() const -> glm::vec2
{
    return size_;
}

auto gfx_gles2_texture::get_pixel_format() const -> data::image::pixel_format
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
