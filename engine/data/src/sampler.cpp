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

#include <aeon/data/sampler.h>

namespace aeon
{
namespace data
{

sampler::sampler(const std::string &name, const std::string &path)
    : name_(name)
    , path_(path)
{
}

auto sampler::get_name() const -> const std::string &
{
    return name_;
}

auto sampler::get_path() const -> const std::string &
{
    return path_;
}

} // namespace data
} // namespace aeon
