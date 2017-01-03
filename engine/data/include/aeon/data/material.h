/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#include <aeon/common/exception.h>
#include <aeon/utility.h>
#include <string>
#include <map>

namespace aeon
{
namespace data
{

DEFINE_EXCEPTION_OBJECT(material_exception, aeon::common::exception, "Generic Material exception.");

class material : utility::noncopyable
{
public:
    using texture_paths = std::map<std::string, std::string>;

    material(const std::string &shader_path, const texture_paths &textures);
    ~material() = default;

    material(material &&other) noexcept
        : shader_path_(std::move(other.shader_path_))
        , texture_paths_(std::move(other.texture_paths_))
    {
    }

    material &operator=(material &&other) noexcept
    {
        shader_path_ = std::move(other.shader_path_);
        texture_paths_ = std::move(other.texture_paths_);
        return *this;
    }

    const std::string &get_shader_path() const;

    const std::string &get_texture_path_by_name(const std::string &name) const;
    const texture_paths &get_texture_paths() const;

private:
    std::string shader_path_;
    texture_paths texture_paths_;
};

} // namespace data
} // namespace aeon
