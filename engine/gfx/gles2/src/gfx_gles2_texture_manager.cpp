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

#include <gfx/gles2/gfx_gles2_texture_manager.h>
#include <gfx/gles2/gfx_gles2_texture.h>
#include <resources/image.h>
#include <gfx/gl_common/check_gl_error.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

gfx_gles2_texture_manager::gfx_gles2_texture_manager()
    : logger_(common::logger::get_singleton(), "Gfx::GLES2::TextureManager")
{
}

texture_ptr gfx_gles2_texture_manager::__load(resources::image_ptr image)
{
    gfx_gles2_texture_ptr t = std::make_shared<gfx_gles2_texture>(image);

    GLuint handle = 0;
    glGenTextures(1, &handle);
    AEON_CHECK_GL_ERROR();

    AEON_LOG_TRACE(logger_) << "Created Texture (GL handle: " << handle << ")." << std::endl;

    glBindTexture(GL_TEXTURE_2D, handle);
    AEON_CHECK_GL_ERROR();

    const data::image &image_data = image->get_data();
    GLint pixelformat = __image_pixelformat_to_gl(image_data.get_pixelformat());
    GLsizei width = image_data.get_width();
    GLsizei height = image_data.get_height();
    glTexImage2D(GL_TEXTURE_2D, 0, pixelformat, width, height, 0, pixelformat, GL_UNSIGNED_BYTE,
                 image_data.get_data().data());
    AEON_CHECK_GL_ERROR();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    AEON_CHECK_GL_ERROR();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    AEON_CHECK_GL_ERROR();

    t->handle_ = handle;
    t->size_ = glm::vec2(width, height);

    return t;
}

GLint gfx_gles2_texture_manager::__image_pixelformat_to_gl(data::image::pixel_format format)
{
    switch (format)
    {
        case data::image::pixel_format::rgb:
            return GL_RGB;
        case data::image::pixel_format::rgba:
            return GL_RGBA;
        default:
        {
            AEON_LOG_WARNING(logger_) << "Unknown or invalid image pixel format, assuming RGBA. (This is a bug!)"
                                      << std::endl;
            // TODO: Error condition?
            return GL_RGBA;
        }
    }
}

} // namespace gles2
} // namespace gfx
} // namespace aeon
