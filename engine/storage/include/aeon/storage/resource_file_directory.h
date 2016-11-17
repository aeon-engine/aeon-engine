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

#include <aeon/storage/resource_file_chunk.h>
#include <string>
#include <vector>
#include <memory>

namespace aeon
{
namespace storage
{

class resource_file_directory
{
public:
    resource_file_directory(resource_file_directory *parent, const std::string &name, const std::uint64_t id);
    ~resource_file_directory() = default;

    auto get_name() const -> const std::string &;
    void set_name(const std::string &name);

    auto get_id() const -> std::uint64_t;

    auto get_subdirectories() const -> const std::vector<std::unique_ptr<resource_file_directory>> &;
    auto get_file_chunks() const -> const std::vector<std::unique_ptr<resource_file_chunk>> &;

    auto get_directory(const std::string &name) -> resource_file_directory *;
    auto get_file_chunk(const std::string &name) -> resource_file_chunk *;

private:
    resource_file_directory *parent_;

    std::string name_;
    std::uint64_t id_;

    std::vector<std::unique_ptr<resource_file_directory>> directories_;
    std::vector<std::unique_ptr<resource_file_chunk>> file_chunks_;
};

} // namespace storage
} // namespace aeon
