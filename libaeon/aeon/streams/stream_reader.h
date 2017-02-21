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

class stream;
template <typename T>
class stream_reader : utility::noncopyable
{
public:
    explicit stream_reader(T &streamref)
        : stream_(streamref)
    {
    }

#define STREAM_READER_READ_OPERATOR(Type)                                                                              \
    stream_reader &operator>>(Type &value)                                                                             \
    {                                                                                                                  \
        if (stream_.read((std::uint8_t *)&value, sizeof(Type)) != sizeof(Type))                                        \
        {                                                                                                              \
            throw std::runtime_error("Operator read failed on stream.");                                               \
        }                                                                                                              \
        return *this;                                                                                                  \
    }

    STREAM_READER_READ_OPERATOR(std::int8_t)
    STREAM_READER_READ_OPERATOR(std::int16_t)
    STREAM_READER_READ_OPERATOR(std::int32_t)
    STREAM_READER_READ_OPERATOR(std::int64_t)

    STREAM_READER_READ_OPERATOR(std::uint8_t)
    STREAM_READER_READ_OPERATOR(std::uint16_t)
    STREAM_READER_READ_OPERATOR(std::uint32_t)
    STREAM_READER_READ_OPERATOR(std::uint64_t)

    STREAM_READER_READ_OPERATOR(float)
    STREAM_READER_READ_OPERATOR(double)

    template <class U = T>
    typename std::enable_if<std::is_same<U, file_stream>::value, std::string>::type read_line()
    {
        std::string line = stream_.read_line();
        return line;
    }

    template <class U = T>
    typename std::enable_if<!std::is_same<U, file_stream>::value, std::string>::type read_line()
    {
        std::uint8_t peek_data = 0;
        std::ptrdiff_t offset = 0;
        std::size_t stringlength = 0;

        while (stream_.peek(peek_data, offset++))
        {
            ++stringlength;

            if (peek_data == '\n')
                break;
        }

        if (stringlength == 0)
            return std::string();

        std::string line;
        line.resize(stringlength);
        stringlength = stream_.read(reinterpret_cast<std::uint8_t *>(&line[0]), stringlength);

        if (stringlength == 0)
            return std::string();

        int strip_characters = 1;

        if (stringlength >= 2)
        {
            if (line[stringlength - 2] == '\r')
                ++strip_characters;
        }

        line.resize(stringlength - strip_characters);

        return line;
    }

protected:
    T &stream_;
};

} // namespace streams
} // namespace aeon
