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

#include <aeon/gfx/gles2/gfx_gles2_texture_manager.h>
#include <aeon/gfx/gles2/gfx_gles2_texture.h>
#include <aeon/data/image.h>
#include <aeon/gfx/gl_common/check_gl_error.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

gfx_gles2_texture_manager::gfx_gles2_texture_manager()
    : logger_(common::logger::get_singleton(), "Gfx::Gles2::TextureManager")
{
}

auto gfx_gles2_texture_manager::create(const data::image &image_data) -> std::shared_ptr<texture>
{
    auto t = std::make_shared<gfx_gles2_texture>();

    GLuint handle = 0;
    glGenTextures(1, &handle);
    AEON_CHECK_GL_ERROR();

    AEON_LOG_TRACE(logger_) << "Created Texture (GL handle: " << handle << ")." << std::endl;

    glBindTexture(GL_TEXTURE_2D, handle);
    AEON_CHECK_GL_ERROR();

    auto pixelformat = __image_pixelformat_to_gl(image_data.get_pixelformat());
    auto width = image_data.get_width();
    auto height = image_data.get_height();

    switch (image_data.get_pixelformat())
    {
        case data::image::pixel_format::rgb:
        case data::image::pixel_format::rgba:
        {
            if (image_data.get_mipmap_count() != 0)
                AEON_LOG_WARNING(logger_) << "Mipmapping for RGB(A) images is currently not supported." << std::endl;

            glTexImage2D(GL_TEXTURE_2D, 0, pixelformat, width, height, 0, pixelformat, GL_UNSIGNED_BYTE,
                         image_data.get_data().data());
            break;
        }
        case data::image::pixel_format::dxt1:
        case data::image::pixel_format::dxt3:
        case data::image::pixel_format::dxt5:
        {
            throw std::runtime_error("DXT textures currently not supported.");
        }
    }

    AEON_CHECK_GL_ERROR();

    if (image_data.get_mipmap_count() == 0)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        AEON_CHECK_GL_ERROR();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        AEON_CHECK_GL_ERROR();
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        AEON_CHECK_GL_ERROR();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        AEON_CHECK_GL_ERROR();
    }

    t->handle_ = handle;
    t->size_ = glm::vec2(width, height);
    t->pixel_format_ = image_data.get_pixelformat();

    return t;
}

auto gfx_gles2_texture_manager::__image_pixelformat_to_gl(data::image::pixel_format format) const -> GLint
{
    switch (format)
    {
        case data::image::pixel_format::rgb:
            return GL_RGB;
        case data::image::pixel_format::rgba:
            return GL_RGBA;
        case data::image::pixel_format::dxt1:
        case data::image::pixel_format::dxt3:
        case data::image::pixel_format::dxt5:
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
