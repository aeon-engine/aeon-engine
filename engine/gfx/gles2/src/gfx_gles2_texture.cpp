/*
 * Copyright (c) 2012-2017 Robin Degen
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

#include <gfx/gles2/gfx_gles2_texture.h>
#include <gfx/gles2/gfx_gles2_shader.h>
#include <gfx/gl_common/check_gl_error.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

gfx_gles2_texture::gfx_gles2_texture(resources::image_ptr image)
    : gfx::texture(image)
    , logger_(common::logger::get_singleton(), "Gfx::GLES2::Texture")
    , handle_(0)
{
}

gfx_gles2_texture::~gfx_gles2_texture()
{
    AEON_LOG_TRACE(logger_) << "Deleting Texture (GL handle: " << handle_ << ")." << std::endl;
    glDeleteTextures(1, &handle_);
    AEON_CHECK_GL_ERROR();
}

void gfx_gles2_texture::bind(gfx_gles2_shader &s) const
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
