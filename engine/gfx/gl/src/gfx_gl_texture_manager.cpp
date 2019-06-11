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

#include <aeon/gfx/gl/gfx_gl_texture_manager.h>
#include <aeon/gfx/gl/gfx_gl_texture.h>
#include <aeon/gfx/gl_common/check_gl_error.h>
#include <aeon/imaging/dynamic_image.h>
#include <glad/glad.h>
#include <algorithm>

namespace aeon::gfx::gl
{

gfx_gl_texture_manager::gfx_gl_texture_manager()
    : logger_(common::logger::get_singleton(), "Gfx::GL::TextureManager")
{
}

auto gfx_gl_texture_manager::create(const imaging::dynamic_image &image_data) -> std::shared_ptr<texture>
{
    auto t = std::make_shared<gfx_gl_texture>();

    GLuint handle = 0;
    glGenTextures(1, &handle);
    AEON_CHECK_GL_ERROR();

    AEON_LOG_TRACE(logger_) << "Created Texture (GL handle: " << handle << ")." << std::endl;

    glBindTexture(GL_TEXTURE_2D, handle);
    AEON_CHECK_GL_ERROR();

    auto pixelformat = __image_pixelformat_to_gl(imaging::encoding(image_data));
    auto width = imaging::width(image_data);
    auto height = imaging::height(image_data);

    switch (imaging::encoding(image_data))
    {
        case imaging::pixel_encoding::rgb24:
        case imaging::pixel_encoding::rgba32:
        case imaging::pixel_encoding::bgr24:
        case imaging::pixel_encoding::bgra32:
            glTexImage2D(GL_TEXTURE_2D, 0, pixelformat, width, height, 0, pixelformat, GL_UNSIGNED_BYTE,
                         imaging::raw_data(image_data));
            break;
        case imaging::pixel_encoding::unsigned8:
        case imaging::pixel_encoding::unsigned16:
        case imaging::pixel_encoding::unsigned32:
        case imaging::pixel_encoding::float32:
        default:
        {
            AEON_LOG_WARNING(logger_)
                << "Unknown or invalid image pixel format. Did not create a texture (This is a bug!)" << std::endl;
        }
    }

    AEON_CHECK_GL_ERROR();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    AEON_CHECK_GL_ERROR();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    AEON_CHECK_GL_ERROR();

    t->handle_ = handle;
    t->size_ = math::vector2<float>{width, height};
    t->pixel_format_ = imaging::encoding(image_data);

    return t;
}

auto gfx_gl_texture_manager::__image_pixelformat_to_gl(const imaging::pixel_encoding format) const -> GLint
{
    switch (format)
    {
        case imaging::pixel_encoding::rgb24:
            return GL_RGB;
        case imaging::pixel_encoding::rgba32:
            return GL_RGBA;
        case imaging::pixel_encoding::bgr24:
            return GL_BGR;
        case imaging::pixel_encoding::bgra32:
            return GL_BGRA;
        case imaging::pixel_encoding::unsigned8:
        case imaging::pixel_encoding::unsigned16:
        case imaging::pixel_encoding::unsigned32:
        case imaging::pixel_encoding::float32:
        default:
        {
            AEON_LOG_WARNING(logger_) << "Unknown or invalid image pixel format, assuming RGBA. (This is a bug!)"
                                      << std::endl;
            // TODO: Error condition?
            return GL_RGBA;
        }
    }
}
} // namespace aeon::gfx::gl
