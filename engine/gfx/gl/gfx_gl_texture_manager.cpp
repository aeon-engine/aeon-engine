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

#include <gfx/gl/gfx_gl_texture_manager.h>
#include <gfx/gl/gfx_gl_texture.h>
#include <resources/image.h>
#include <GL/glew.h>
#include <gfx/gl_common/check_gl_error.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

gfx_gl_texture_manager::gfx_gl_texture_manager()
    : logger_(common::logger::get_singleton(), "Gfx::GL::TextureManager")
{
}

texture_ptr gfx_gl_texture_manager::create(const data::image &image_data)
{
    gfx_gl_texture_ptr t = std::make_shared<gfx_gl_texture>();

    GLuint handle = 0;
    glGenTextures(1, &handle);
    AEON_CHECK_GL_ERROR();

    AEON_LOG_TRACE(logger_) << "Created Texture (GL handle: " << handle << ")." << std::endl;

    glBindTexture(GL_TEXTURE_2D, handle);
    AEON_CHECK_GL_ERROR();

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

GLint gfx_gl_texture_manager::__image_pixelformat_to_gl(data::image::pixel_format format) const
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

} // namespace gl
} // namespace gfx
} // namespace aeon
