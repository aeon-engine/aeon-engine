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

#include <aeon/platform/platform_file_interface.h>
#include <string>
#include <cstdint>
#include <memory>

namespace aeon
{

namespace platform
{
class platform_filesystem_interface;
class platform_file_interface;
} // namespace platform

namespace storage
{

class resource_file_chunk
{
public:
};

class resource_file
{
public:
    explicit resource_file(const std::string &filename, platform::platform_filesystem_interface &filesystem_interface);
    ~resource_file() = default;

private:
    void __open_existing_file();
    void __open_new_file();

    void __write_file_header();

    std::string filename_;
    platform::platform_filesystem_interface &filesystem_interface_;
    std::shared_ptr<platform::platform_file_interface> file_interface_;
};

} // namespace storage
} // namespace aeon
