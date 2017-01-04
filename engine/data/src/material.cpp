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

#include <aeon/data/material.h>

namespace aeon
{
namespace data
{

material::material(material &&other) noexcept
    : shader_path_(std::move(other.shader_path_))
    , samplers_(std::move(other.samplers_))
{
}

auto material::operator=(material &&other) noexcept -> material &
{
    shader_path_ = std::move(other.shader_path_);
    samplers_ = std::move(other.samplers_);
    return *this;
}

void material::set_shader_path(const std::string &path)
{
    shader_path_ = path;
}

auto material::get_shader_path() const -> const std::string &
{
    return shader_path_;
}

void material::add_sampler(const sampler &sampler)
{
    samplers_[sampler.get_name()] = sampler;
}

auto material::get_sampler_by_name(const std::string &name) const -> sampler
{
    auto result = samplers_.find(name);

    if (result == samplers_.end())
        throw material_exception();

    return result->second;
}

auto material::get_samplers() const -> const std::map<std::string, sampler> &
{
    return samplers_;
}

} // namespace data
} // namespace aeon
