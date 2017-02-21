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

#include <aeon/platform/platform_file_open_mode.h>
#include <aeon/platform/platform_file_interface.h>
#include <aeon/streams.h>
#include <aeon/common/logger.h>
#include <memory>
#include <string>

namespace aeon
{
namespace platform
{
namespace generic
{

// TODO: Exception handling for whole class
class platform_file_interface : public platform::platform_file_interface
{
public:
    explicit platform_file_interface(const std::string &path, const int openmode);
    virtual ~platform_file_interface() override;

    void read(std::vector<std::uint8_t> &buffer) override;
    void read(std::vector<std::uint8_t> &buffer, const int size) override;

    void write(std::vector<std::uint8_t> &buffer) override;
    void write(std::vector<std::uint8_t> &buffer, const int size) override;

    void seek_read(seek_direction direction, const int offset) override;
    void seek_write(seek_direction direction, const int offset) override;

    auto get_size() const -> int override;

private:
    auto __open_mode_to_stream_open_mode(const int openmode) const -> int;
    auto __open_mode_to_stream_file_mode(const int openmode) const -> streams::file_mode;

    auto __to_streams_seek_direction(const seek_direction direction) const -> streams::stream::seek_direction;

    logger::logger logger_;

    streams::file_stream_ptr stream_;
};

} // namespace generic
} // namespace platform
} // namespace aeon
