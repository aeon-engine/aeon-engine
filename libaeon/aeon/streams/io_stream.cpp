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

namespace aeon
{
namespace streams
{

io_stream::io_stream(int mode /*= aeon::streams::access_mode::write*/)
    : aeon::streams::stream(mode)
{
}

std::size_t io_stream::read(std::uint8_t *data, std::size_t size)
{
    if (!is_readable())
        throw io_stream_exception();

    if (!data || size == 0)
        throw io_stream_exception();

    return fread(data, 1, size, stdin);
}

std::size_t io_stream::write(const std::uint8_t *data, std::size_t size)
{
    if (!is_writable())
        throw io_stream_exception();

    if (!data || size == 0)
        throw io_stream_exception();

    return fwrite(data, 1, size, stdout);
}

bool io_stream::peek(std::uint8_t &data, std::ptrdiff_t /*= 0*/)
{
    if (!is_readable())
        throw io_stream_exception();

    int c = fgetc(stdin);

    if (c == EOF)
        return false;

    // TODO: research if there is a good alternative for this.
    if (ungetc(c, stdin) == EOF)
        return false;

    data = static_cast<std::uint8_t>(c);
    return true;
}

bool io_stream::seek(std::ptrdiff_t, seek_direction)
{
    return false;
}

bool io_stream::seekw(std::ptrdiff_t, seek_direction)
{
    return false;
}

std::size_t io_stream::tell()
{
    return 0;
}

std::size_t io_stream::tellw()
{
    return 0;
}

bool io_stream::eof() const
{
    return (feof(stdin) != 0);
}

void io_stream::flush()
{
    fflush(stdout);
}

std::size_t io_stream::size() const
{
    return 0;
}

bool io_stream::good() const
{
    return true;
}

} // namespace streams
} // namespace aeon
