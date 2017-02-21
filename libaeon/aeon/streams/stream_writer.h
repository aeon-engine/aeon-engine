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
class stream_writer : utility::noncopyable
{
public:
    explicit stream_writer(stream &streamref)
        : stream_(streamref)
    {
    }

#define STREAM_WRITER_WRITE_OPERATOR(Type)                                                                             \
    stream_writer &operator<<(Type &value)                                                                             \
    {                                                                                                                  \
        if (stream_.write((std::uint8_t *)&value, sizeof(Type)) != sizeof(Type))                                       \
        {                                                                                                              \
            throw std::runtime_error("Operator write failed on stream.");                                              \
        }                                                                                                              \
        return *this;                                                                                                  \
    }

    STREAM_WRITER_WRITE_OPERATOR(std::int8_t)
    STREAM_WRITER_WRITE_OPERATOR(std::int16_t)
    STREAM_WRITER_WRITE_OPERATOR(std::int32_t)
    STREAM_WRITER_WRITE_OPERATOR(std::int64_t)

    STREAM_WRITER_WRITE_OPERATOR(std::uint8_t)
    STREAM_WRITER_WRITE_OPERATOR(std::uint16_t)
    STREAM_WRITER_WRITE_OPERATOR(std::uint32_t)
    STREAM_WRITER_WRITE_OPERATOR(std::uint64_t)

    STREAM_WRITER_WRITE_OPERATOR(float)
    STREAM_WRITER_WRITE_OPERATOR(double)

    stream_writer &operator<<(const std::string &value)
    {
        std::size_t string_length = value.size();
        if (stream_.write(reinterpret_cast<const std::uint8_t *>(value.c_str()), string_length) != string_length)
        {
            throw std::runtime_error("Operator write failed on stream.");
        }
        return *this;
    }

    void write_line(const std::string &line) const
    {
        stream_.write(reinterpret_cast<const std::uint8_t *>(line.c_str()), line.size());
        stream_.write(reinterpret_cast<const std::uint8_t *>("\n"), 1);
    }

protected:
    stream &stream_;
};

} // namespace streams
} // namespace aeon
