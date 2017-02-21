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

#include <aeon/streams.h>

#if (AEON_PLATFORM_OS_WINDOWS)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

namespace aeon
{
namespace streams
{

io_stream_colors_mixin::io_stream_colors_mixin()
    : enabled_(true)
{
}

void io_stream_colors_mixin::set_color(color c, weight w /*= weight::normal*/) const
{
    if (!enabled_)
        return;

#if (AEON_PLATFORM_OS_WINDOWS)
    static HANDLE std_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    int intensity = 0;
    if (w == weight::bold)
        intensity = FOREGROUND_INTENSITY;

    switch (c)
    {
        case color::black:
            SetConsoleTextAttribute(std_handle, 0);
            break;
        case color::red:
            SetConsoleTextAttribute(std_handle, static_cast<WORD>(FOREGROUND_RED | intensity));
            break;
        case color::green:
            SetConsoleTextAttribute(std_handle, static_cast<WORD>(FOREGROUND_GREEN | intensity));
            break;
        case color::yellow:
            SetConsoleTextAttribute(std_handle, static_cast<WORD>(FOREGROUND_RED | FOREGROUND_GREEN | intensity));
            break;
        case color::blue:
            SetConsoleTextAttribute(std_handle, static_cast<WORD>(FOREGROUND_BLUE | intensity));
            break;
        case color::magenta:
            SetConsoleTextAttribute(std_handle, static_cast<WORD>(FOREGROUND_RED | FOREGROUND_BLUE | intensity));
            break;
        case color::cyan:
            SetConsoleTextAttribute(std_handle, static_cast<WORD>(FOREGROUND_GREEN | FOREGROUND_BLUE | intensity));
            break;
        case color::white:
            SetConsoleTextAttribute(std_handle,
                                    static_cast<WORD>(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | intensity));
            break;
    }
#else
    reset_color();

    if (w == weight::bold)
    {
        std::cout << AEON_TERM_COLOR_BOLD;
    }

    switch (c)
    {
        case color::black:
            std::cout << AEON_TERM_COLOR_BLACK;
            break;
        case color::red:
            std::cout << AEON_TERM_COLOR_RED;
            break;
        case color::green:
            std::cout << AEON_TERM_COLOR_GREEN;
            break;
        case color::yellow:
            std::cout << AEON_TERM_COLOR_YELLOW;
            break;
        case color::blue:
            std::cout << AEON_TERM_COLOR_BLUE;
            break;
        case color::magenta:
            std::cout << AEON_TERM_COLOR_MAGENTA;
            break;
        case color::cyan:
            std::cout << AEON_TERM_COLOR_CYAN;
            break;
        case color::white:
            std::cout << AEON_TERM_COLOR_WHITE;
            break;
    }
#endif
}

void io_stream_colors_mixin::reset_color() const
{
    if (!enabled_)
        return;

#if (AEON_PLATFORM_OS_WINDOWS)
    static HANDLE std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(std_handle, 0);
#else
    std::cout << AEON_TERM_COLOR_RESET;
#endif
}

void io_stream_colors_mixin::enable_colors()
{
    enabled_ = true;
}

void io_stream_colors_mixin::disable_colors()
{
    enabled_ = false;
}

} // namespace streams
} // namespace aeon
