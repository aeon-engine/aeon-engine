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

file_stream::file_stream(const std::string &filename, int mode, file_mode fm /*= file_mode::binary*/)
    : stream(mode)
    , size_(0)
    , filename_(filename)
{
    fstream_.open(filename, to_ios_open_mode_(mode, fm));

    if (!fstream_.good())
        throw file_stream_exception();

    // Note: We can not call is_readable here since it's a virtual method.
    if (fstream_.good() && ((access_mode_ & access_mode::read) != 0))
    {
        fstream_.seekg(0, std::ios::end);
        size_ = static_cast<std::size_t>(fstream_.tellg());
        fstream_.seekg(0, std::ios::beg);
    }
}

file_stream::file_stream(const std::string &filename, file_mode fm /*= file_mode::binary*/)
    : file_stream(filename, access_mode::read, fm)
{
}

std::size_t file_stream::read(std::uint8_t *data, std::size_t size)
{
    if (!is_readable())
        throw file_stream_exception();

    if (!data || size == 0)
        throw file_stream_exception();

    fstream_.read(reinterpret_cast<char *>(data), size);

    if (fstream_.eof())
        return static_cast<std::size_t>(fstream_.gcount());

    if (fstream_.fail())
        return 0;

    return size;
}

std::size_t file_stream::write(const std::uint8_t *data, std::size_t size)
{
    if (!is_writable())
        throw file_stream_exception();

    if (!data || size == 0)
        throw file_stream_exception();

    fstream_.write(reinterpret_cast<const char *>(data), size);

    if (fstream_.fail())
        return 0;

    return size;
}

bool file_stream::peek(std::uint8_t &data, std::ptrdiff_t offset /* = 0 */)
{
    if (!is_readable())
        throw file_stream_exception();

    std::size_t original_offset = 0;

    if (offset != 0)
    {
        original_offset = static_cast<std::size_t>(fstream_.tellg());
        fstream_.seekg(original_offset + offset, std::ios::beg);

        if (fstream_.fail())
            return false;
    }

    int peek_val = fstream_.peek();

    if (peek_val == EOF)
        return false;

    data = static_cast<std::uint8_t>(peek_val);

    if (offset != 0)
        fstream_.seekg(original_offset, std::ios::beg);

    return true;
}

bool file_stream::seek(std::ptrdiff_t pos, seek_direction direction)
{
    if (!is_readable())
        throw file_stream_exception();

    fstream_.seekg(pos, seek_direction_to_ios_seekdir_(direction));
    return !fstream_.fail();
}

bool file_stream::seekw(std::ptrdiff_t pos, seek_direction direction)
{
    if (!is_writable())
        throw file_stream_exception();

    fstream_.seekp(pos, seek_direction_to_ios_seekdir_(direction));
    return !fstream_.fail();
}

std::size_t file_stream::tell()
{
    if (!is_readable())
        throw file_stream_exception();

    return static_cast<std::size_t>(fstream_.tellg());
}

std::size_t file_stream::tellw()
{
    if (!is_writable())
        throw file_stream_exception();

    return static_cast<std::size_t>(fstream_.tellp());
}

bool file_stream::eof() const
{
    return fstream_.eof();
}

std::size_t file_stream::size() const
{
    return size_;
}

void file_stream::flush()
{
    fstream_.flush();
}

bool file_stream::good() const
{
    return fstream_.good();
}

std::ios::openmode file_stream::to_ios_open_mode_(int mode, file_mode fm) const
{
    std::ios::openmode openmode_zero = static_cast<std::ios::openmode>(0);

    std::ios::openmode m = (fm == file_mode::binary) ? std::fstream::binary : openmode_zero;
    m |= (mode & access_mode::read) ? std::fstream::in : openmode_zero;
    m |= (mode & access_mode::write) ? std::fstream::out : openmode_zero;
    m |= (mode & access_mode::truncate) ? std::fstream::trunc : openmode_zero;
    return m;
}

std::ios::seekdir file_stream::seek_direction_to_ios_seekdir_(seek_direction direction) const
{
    switch (direction)
    {
        case (seek_direction::begin):
            return std::ios::beg;
        case (seek_direction::current):
            return std::ios::cur;
        case (seek_direction::end):
            return std::ios::end;
    }

    return std::ios::cur;
}

std::string file_stream::read_line()
{
    if (!is_readable())
        throw file_stream_exception();

    if (eof())
        throw file_stream_exception();

    std::string line;
    std::getline(fstream_, line);
    line.erase(line.find_last_not_of("\n\r") + 1);
    return line;
}

void file_stream::write_line(const std::string &line)
{
    if (!is_writable())
        throw file_stream_exception();

    fstream_ << line << std::endl;
}

const std::string &file_stream::get_filename() const
{
    return filename_;
}

} // namespace streams
} // namespace aeon
