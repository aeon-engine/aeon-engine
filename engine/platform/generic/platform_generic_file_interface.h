/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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

#include <platform/platform_file_open_mode.h>
#include <platform/platform_file_interface.h>
#include <common/buffer.h>
#include <aeon/streams.h>
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
    friend class platform_filesystem_interface;

public:
    virtual ~platform_file_interface() override;

    void read(common::buffer_u8 &buffer) override;
    void read(common::buffer_u8 &buffer, int size) override;

    void write(common::buffer_u8 &buffer) override;
    void write(common::buffer_u8 &buffer, int size) override;

    void seek_read(seek_direction direction, int offset) override;
    void seek_write(seek_direction direction, int offset) override;

    int get_size() override;

private:
    platform_file_interface(const std::string &path, int openmode);

    aeon::streams::stream::seek_direction __to_streams_seek_direction(seek_direction direction);

    aeon::streams::file_stream_ptr stream_;
};

using platform_file_interface_ptr = std::shared_ptr<platform_file_interface>;

} // namespace generic
} // namespace platform
} // namespace aeon
