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
#include <aeon/data/sampler.h>
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
    material() = default;
    ~material() = default;

    material(material &&other) noexcept;
    auto operator=(material &&other) noexcept -> material &;

    void set_shader_path(const std::string &path);

    auto get_shader_path() const -> const std::string &;

    void add_sampler(const sampler &sampler);

    auto get_sampler_by_name(const std::string &name) const -> sampler;

    auto get_samplers() const -> const std::map<std::string, sampler> &;

private:
    std::string shader_path_;
    std::map<std::string, sampler> samplers_;
};

} // namespace data
} // namespace aeon
