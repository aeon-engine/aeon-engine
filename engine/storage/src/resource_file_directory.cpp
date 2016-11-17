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

#include <aeon/storage/resource_file_directory.h>

namespace aeon
{
namespace storage
{

resource_file_directory::resource_file_directory(resource_file_directory *parent, const std::string &name, const std::uint64_t id)
    : name_(name)
    , id_(id)
{
}

auto resource_file_directory::get_name() const -> const std::string &
{
    return name_;
}

void resource_file_directory::set_name(const std::string &name)
{
    name_ = name;
}

auto resource_file_directory::get_id() const -> std::uint64_t
{
    return id_;
}

auto resource_file_directory::get_subdirectories() const -> const std::vector<std::unique_ptr<resource_file_directory>> &
{
    return directories_;
}

auto resource_file_directory::get_file_chunks() const -> const std::vector<std::unique_ptr<resource_file_chunk>> &
{
    return file_chunks_;
}

auto resource_file_directory::get_directory(const std::string &name) -> resource_file_directory *
{
    for (auto &directory : directories_)
    {
        if (directory->get_name() == name)
        {
            return directory.get();
        }
    }

    return nullptr;
}

auto resource_file_directory::get_file_chunk(const std::string &name) -> resource_file_chunk *
{
    for (auto &file_chunk : file_chunks_)
    {
        if (file_chunk->get_name() == name)
        {
            return file_chunk.get();
        }
    }

    return nullptr;
}

} // namespace storage
} // namespace aeon
