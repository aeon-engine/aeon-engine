/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#include <aeon/platform/generic/platform_generic_file_interface.h>

namespace aeon
{
namespace platform
{
namespace generic
{

platform_file_interface::platform_file_interface(const std::string &path, int openmode)
    : platform::platform_file_interface(path, openmode)
    , logger_(common::logger::get_singleton(), "Platform::Generic::Filesystem")
    , stream_(nullptr)
{
    AEON_LOG_DEBUG(logger_) << "Opening file " << path << " with file stream." << std::endl;

    try
    {
        int access_mode = __open_mode_to_stream_open_mode(openmode);
        streams::file_mode file_mode = __open_mode_to_stream_file_mode(openmode);
        stream_ = std::make_shared<streams::file_stream>(path, access_mode, file_mode);
    }
    catch (streams::file_stream_exception &)
    {
        throw platform_file_open_exception();
    }
}

platform_file_interface::~platform_file_interface()
{
    AEON_LOG_DEBUG(logger_) << "Closing file " << stream_->get_filename() << "." << std::endl;
}

void platform_file_interface::read(std::vector<std::uint8_t> &buffer)
{
    read(buffer, static_cast<int>(stream_->size()));
}

void platform_file_interface::read(std::vector<std::uint8_t> &buffer, int size)
{
    AEON_LOG_TRACE(logger_) << "Reading " << size << " bytes from " << stream_->get_filename() << "." << std::endl;

    buffer.resize(size);
    std::size_t read_size = stream_->read(buffer.data(), size);
    buffer.resize(read_size);
}

void platform_file_interface::write(std::vector<std::uint8_t> &buffer)
{
    AEON_LOG_TRACE(logger_) << "Writing " << stream_->size() << " bytes to " << stream_->get_filename() << "."
                            << std::endl;

    stream_->write(buffer.data(), buffer.size());
}

void platform_file_interface::write(std::vector<std::uint8_t> &buffer, int size)
{
    AEON_LOG_TRACE(logger_) << "Writing " << size << " bytes to " << stream_->get_filename() << "." << std::endl;

    stream_->write(buffer.data(), size);
}

void platform_file_interface::seek_read(seek_direction direction, int offset)
{
    stream_->seek(offset, __to_streams_seek_direction(direction));
}

void platform_file_interface::seek_write(seek_direction direction, int offset)
{
    stream_->seekw(offset, __to_streams_seek_direction(direction));
}

int platform_file_interface::get_size()
{
    return static_cast<int>(stream_->size());
}

int platform_file_interface::__open_mode_to_stream_open_mode(const int openmode) const
{
    int access_mode = 0;
    access_mode |= (openmode & file_open_mode::read) ? aeon::streams::access_mode::read : 0;
    access_mode |= (openmode & file_open_mode::write) ? aeon::streams::access_mode::write : 0;
    access_mode |= (openmode & file_open_mode::truncate) ? aeon::streams::access_mode::truncate : 0;
    return access_mode;
}

streams::file_mode platform_file_interface::__open_mode_to_stream_file_mode(const int openmode) const
{
    return (openmode & file_open_mode::binary) ? streams::file_mode::binary : streams::file_mode::text;
}

streams::stream::seek_direction platform_file_interface::__to_streams_seek_direction(seek_direction direction) const
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
} // namespace platform
} // namespace aeon
