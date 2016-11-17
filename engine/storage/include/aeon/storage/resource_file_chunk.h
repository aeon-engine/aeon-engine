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

#include <string>

namespace aeon
{
namespace storage
{

class resource_file_directory;

class resource_file_chunk
{
public:
    resource_file_chunk(resource_file_directory &parent, const std::string &name, const std::uint64_t id);
    ~resource_file_chunk();

    auto get_name() const -> const std::string &;
    void set_name(const std::string &name);

    auto get_parent() const -> resource_file_directory &;

private:
    resource_file_directory &parent_;

    std::string name_;
    std::uint64_t id_;
    std::uint64_t name_offset_;
    std::uint32_t type_id_;
    std::uint32_t flags_;
    std::uint64_t offset_;
    std::uint64_t reserved_size_;
    std::uint64_t compressed_size_;
    std::uint64_t actual_size_;
};

} // namespace storage
} // namespace aeon
