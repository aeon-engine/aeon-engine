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

#include <aeon/gfx/gl_common/check_gl_error.h>
#include <aeon/common/logger.h>
#include <aeon/logger/logger.h>

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
    auto count = 0;
    logger::logger logger(common::logger::get_singleton(), "Gfx::GL::Debug");

    auto result = glGetError();
    while (result != GL_NO_ERROR)
    {
        if (++count >= 100)
        {
            AEON_LOG_FATAL(logger) << "Too many OpenGL errors detected (> 100)" << std::endl;
            break;
        }

        auto error_message = std::string();
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
