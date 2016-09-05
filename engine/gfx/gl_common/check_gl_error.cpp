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

#include <gfx/gl_common/check_gl_error.h>
#include <common/logger.h>

#ifdef AEON_GFX_GL
#include <GL/glew.h>
#endif

#ifdef AEON_GFX_GLES2
#include <GLES2/gl2.h>
#endif

namespace aeon
{
namespace gfx
{
namespace gl_common
{

#ifdef AEON_ENABLE_GL_ERROR_CHECKS
void check_gl_error(const char *file, int line)
{
    int count = 0;
    aeon::logger::logger logger(common::logger::get_singleton(), "Gfx::GL::Debug");

    GLenum result = glGetError();
    while (result != GL_NO_ERROR)
    {
        if (++count >= 100)
        {
            AEON_LOG_FATAL(logger) << "Too many OpenGL errors detected (> 100)" << std::endl;
            break;
        }

        std::string error_message;
        switch (result)
        {
            case GL_INVALID_ENUM:
                error_message = "Invalid enum.";
                break;
            case GL_INVALID_VALUE:
                error_message = "Invalid value.";
                break;
            case GL_INVALID_OPERATION:
                error_message = "Invalid operation.";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error_message = "Invalid framebuffer operation.";
                break;
            case GL_OUT_OF_MEMORY:
                error_message = "Out of memory";
                break;
            default:
                error_message = "Unknown error.";
        }

        AEON_LOG_ERROR(logger) << "OpenGL error detected in " << file << ":" << line
            << ". Description: " << error_message << "." << std::endl;

        result = glGetError();
    }
}
#endif

} // namespace gl
} // namespace gfx
} // namespace aeon
