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

#include <platform/generic/platform_generic_file_interface.h>

namespace aeon
{
namespace platform
{
namespace generic
{

platform_file_interface::platform_file_interface(const std::string &path, int openmode) :
    platform::platform_file_interface(path, openmode)
{
}

platform_file_interface::~platform_file_interface()
{
}

void platform_file_interface::read(common::buffer_u8& buffer)
{
}

void platform_file_interface::read(common::buffer_u8& buffer, int size)
{
}

void platform_file_interface::write(common::buffer_u8& buffer)
{
}

void platform_file_interface::write(common::buffer_u8& buffer, int size)
{
}

void platform_file_interface::seek_read(seek_direction direction, int offset)
{
}

void platform_file_interface::seek_write(seek_direction direction, int offset)
{
}

int platform_file_interface::get_size()
{
    return 0;
}

} // namespace generic
} // namespace platform
} // namespace aeon
