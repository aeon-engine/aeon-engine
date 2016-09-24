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

#include <data/material.h>

namespace aeon
{
namespace data
{

material::material(const std::string &shader_path, const material::texture_paths &textures)
    : shader_path_(shader_path)
    , texture_paths_(textures)
{
}

const std::string &material::get_shader_path() const
{
    return shader_path_;
}

const std::string &material::get_texture_path_by_name(const std::string &name) const
{
    auto itr = texture_paths_.find(name);

    if (itr == texture_paths_.end())
        throw material_exception();

    return itr->second;
}

const material::texture_paths &material::get_texture_paths() const
{
    return texture_paths_;
}

} // namespace data
} // namespace aeon
