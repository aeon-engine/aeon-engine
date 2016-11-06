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
