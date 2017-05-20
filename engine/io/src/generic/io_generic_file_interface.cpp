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

#include <aeon/io/generic/io_generic_file_interface.h>

namespace aeon
{
namespace io
{
namespace generic
{

io_generic_file_interface::io_generic_file_interface(const std::string &path, const int openmode)
    : io::io_file_interface()
    , logger_(common::logger::get_singleton(), "io::Generic::Filesystem")
    , stream_(nullptr)
{
    AEON_LOG_DEBUG(logger_) << "Opening file " << path << " with file stream." << std::endl;

    try
    {
        int access_mode = __open_mode_to_stream_open_mode(openmode);
        streams::file_mode file_mode = __open_mode_to_stream_file_mode(openmode);
        stream_ = std::make_unique<streams::file_stream>(path, access_mode, file_mode);
    }
    catch (streams::file_stream_exception &)
    {
        throw io_file_open_exception();
    }
}

io_generic_file_interface::~io_generic_file_interface()
{
    AEON_LOG_DEBUG(logger_) << "Closing file " << stream_->get_filename() << "." << std::endl;
}

std::size_t io_generic_file_interface::read(std::uint8_t *data, std::size_t size)
{
    AEON_LOG_TRACE(logger_) << "Reading " << size << " bytes from " << stream_->get_filename() << "." << std::endl;
    return stream_->read(data, size);
}

std::size_t io_generic_file_interface::write(const std::uint8_t *data, std::size_t size)
{
    AEON_LOG_TRACE(logger_) << "Writing " << stream_->size() << " bytes to " << stream_->get_filename() << "."
                            << std::endl;
    return stream_->write(data, size);
}

bool io_generic_file_interface::peek(std::uint8_t &data, std::ptrdiff_t offset)
{
    return stream_->peek(data, offset);
}

bool io_generic_file_interface::seek(std::ptrdiff_t pos, seek_direction direction)
{
    return stream_->seek(pos, direction);
}

bool io_generic_file_interface::seekw(std::ptrdiff_t pos, seek_direction direction)
{
    return stream_->seekw(pos, direction);
}

std::size_t io_generic_file_interface::tell()
{
    return stream_->tell();
}

std::size_t io_generic_file_interface::tellw()
{
    return stream_->tellw();
}

bool io_generic_file_interface::eof() const
{
    return stream_->eof();
}

std::size_t io_generic_file_interface::size() const
{
    return stream_->size();
}

void io_generic_file_interface::flush()
{
    stream_->flush();
}

bool io_generic_file_interface::good() const
{
    return stream_->good();
}

auto io_generic_file_interface::__open_mode_to_stream_open_mode(const int openmode) const -> int
{
    int access_mode = 0;
    access_mode |= (openmode & file_open_mode::read) ? streams::access_mode::read : 0;
    access_mode |= (openmode & file_open_mode::write) ? streams::access_mode::write : 0;
    access_mode |= (openmode & file_open_mode::truncate) ? streams::access_mode::truncate : 0;
    return access_mode;
}

auto io_generic_file_interface::__open_mode_to_stream_file_mode(const int openmode) const -> streams::file_mode
{
    return (openmode & file_open_mode::binary) ? streams::file_mode::binary : streams::file_mode::text;
}

auto io_generic_file_interface::__to_streams_seek_direction(const seek_direction direction) const
    -> streams::stream::seek_direction
{
    switch (direction)
    {
        default:
        case seek_direction::begin:
            return streams::stream::seek_direction::begin;
        case seek_direction::current:
            return streams::stream::seek_direction::current;
        case seek_direction::end:
            return streams::stream::seek_direction::end;
    }
}

} // namespace generic
} // namespace io
} // namespace aeon
