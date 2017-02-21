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

/* Color codes for colored console output. Can be used like this:
 * std::cout << AEON_TERM_COLOR_BLUE << "Blue! "
 *     << AEON_TERM_COLOR_RESET << "Normal!" << std::endl;
 */

// TODO: Just checking for windows may not be sufficient.
#if (!AEON_PLATFORM_OS_WINDOWS)
#define AEON_TERM_COLOR_RESET "\033[0m"
#define AEON_TERM_COLOR_BOLD "\033[1m"
#define AEON_TERM_COLOR_BLACK "\033[30m"
#define AEON_TERM_COLOR_RED "\033[31m"
#define AEON_TERM_COLOR_GREEN "\033[32m"
#define AEON_TERM_COLOR_YELLOW "\033[33m"
#define AEON_TERM_COLOR_BLUE "\033[34m"
#define AEON_TERM_COLOR_MAGENTA "\033[35m"
#define AEON_TERM_COLOR_CYAN "\033[36m"
#define AEON_TERM_COLOR_WHITE "\033[37m"
#endif // AEON_UTILITY_OS_WINDOWS
