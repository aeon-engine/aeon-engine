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

#pragma once

#include <build_config.h>

#ifdef AEON_ENABLE_GL_ERROR_CHECKS
/*!
 * Check for OpenGL errors through glGetError and report them in the console.
 */
#define AEON_CHECK_GL_ERROR() aeon::gfx::gl_common::check_gl_error(__FILE__, __LINE__)
#else
#define AEON_CHECK_GL_ERROR()                                                                                          \
    do                                                                                                                 \
    {                                                                                                                  \
    } while (0)
#endif

namespace aeon
{
namespace gfx
{
namespace gl_common
{

#ifdef AEON_ENABLE_GL_ERROR_CHECKS
/*!
 * Internal function used by the AEON_CHECK_GL_ERROR macro.
 */
void check_gl_error(const char *file, int line);
#endif

} // namespace gl_common
} // namespace gfx
} // namespace aeon
