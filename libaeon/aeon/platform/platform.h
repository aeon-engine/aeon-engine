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

/* This header defines one or more of the following macro's:
 *
 * AEON_PLATFORM_OS_WINDOWS
 * AEON_PLATFORM_OS_WINDOWS_CYGWIN
 * AEON_PLATFORM_OS_LINUX
 * AEON_PLATFORM_OS_OSX
 * AEON_PLATFORM_OS_BSD
 * AEON_PLATFORM_OS_ANDROID
 * AEON_PLATFORM_OS_IOS
 * AEON_PLATFORM_OS_UNIX
 */

#if (defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__))
#define AEON_PLATFORM_OS_WINDOWS 1
#endif

#if (defined(__CYGWIN__))
#define AEON_PLATFORM_OS_WINDOWS_CYGWIN 1
#endif

#if (defined(linux) || defined(__linux))
#define AEON_PLATFORM_OS_LINUX 1
#endif

#if (defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__)))
#define AEON_PLATFORM_OS_OSX 1
#endif

#if (defined(BSD) || defined(_SYSTYPE_BSD))
#define AEON_PLATFORM_OS_BSD 1
#endif

#if (__ANDROID__)
#define AEON_PLATFORM_OS_ANDROID 1
#endif

#if (defined(__APPLE__) && defined(__MACH__) && defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__))
#define AEON_PLATFORM_OS_IOS
#endif

#if (defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE))
#define AEON_PLATFORM_OS_UNIX 1
#endif
