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

#include <aeon/storage/resource_file_chunk.h>

namespace aeon
{
namespace storage
{

resource_file_chunk::resource_file_chunk(resource_file_directory &parent, const std::string &name, const std::uint64_t id)
    : parent_(parent)
    , name_(name)
    , id_(id)
    , name_offset_(0)
    , type_id_(0)
    , flags_(0)
    , offset_(0)
    , reserved_size_(0)
    , compressed_size_(0)
    , actual_size_(0)
{
}

resource_file_chunk::~resource_file_chunk() = default;

auto resource_file_chunk::get_name() const -> const std::string &
{
    return name_;
}

void resource_file_chunk::set_name(const std::string &name)
{
    name_ = name;
}

auto resource_file_chunk::get_parent() const -> resource_file_directory &
{
    return parent_;
}

} // namespace storage
} // namespace aeon
