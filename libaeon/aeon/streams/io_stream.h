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

namespace aeon
{
namespace streams
{

class io_stream_exception : public stream_exception
{
};

class io_stream : public stream, public io_stream_colors_mixin
{
public:
    explicit io_stream(int mode = aeon::streams::access_mode::write);

    std::size_t read(std::uint8_t *data, std::size_t size) override;

    std::size_t write(const std::uint8_t *data, std::size_t size) override;

    bool peek(std::uint8_t &data, std::ptrdiff_t offset = 0) override;

    bool seek(std::ptrdiff_t pos, seek_direction direction) override;

    bool seekw(std::ptrdiff_t pos, seek_direction direction) override;

    std::size_t tell() override;

    std::size_t tellw() override;

    bool eof() const override;

    std::size_t size() const override;

    void flush() override;

    bool good() const override;
};

typedef std::shared_ptr<io_stream> io_stream_ptr;

} // namespace streams
} // namespace aeon
