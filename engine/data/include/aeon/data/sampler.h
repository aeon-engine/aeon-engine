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

#include <string>

namespace aeon
{
namespace data
{

class sampler
{
public:
    sampler() = default;
    sampler(const std::string &name, const std::string &path);
    ~sampler() = default;

    sampler(const sampler &other) = default;
    sampler &operator=(const sampler &other) = default;

    sampler(sampler &&other) noexcept = default;
    sampler &operator=(sampler &&other) noexcept = default;

    auto get_name() const -> const std::string &;

    auto get_path() const -> const std::string &;

private:
    std::string name_;
    std::string path_;
};

} // namespace data
} // namespace aeon
