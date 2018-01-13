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

#pragma once

#include <string>

namespace aeon
{
namespace platform
{

enum class buffer_mode
{
    single_buffer,
    double_buffer
};

class window_settings
{
public:
    window_settings(const int width, const int height, const std::string &title);
    ~window_settings() = default;

    auto get_width() const -> int;

    auto get_height() const -> int;

    auto get_title() const -> const std::string &;

    void set_multisample(const unsigned int samples);

    auto get_multisample() const -> int;

    void set_buffer_mode(const buffer_mode mode);

    auto get_buffer_mode() const -> buffer_mode;

private:
    int width_;
    int height_;
    std::string title_;

    unsigned int multisample_;
    buffer_mode buffer_mode_;
};

} // namespace platform
} // namespace aeon
