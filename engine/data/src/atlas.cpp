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

#include <aeon/data/atlas.h>

namespace aeon
{
namespace data
{

atlas::atlas(const std::vector<atlas::region> &regions)
    : regions_(regions)
{
}

void atlas::push_back(const atlas::region &region)
{
    regions_.push_back(region);
}

auto atlas::get_regions() const -> const std::vector<region> &
{
    return regions_;
}

auto atlas::at(const unsigned int index) const -> const atlas::region &
{
    if (index >= regions_.size())
        throw atlas_exception();

    return regions_.at(index);
}

auto atlas::at(const std::string &name) const -> const atlas::region &
{
    for (const auto &region : regions_)
    {
        if (region.name == name)
            return region;
    }

    throw atlas_exception();
}

auto atlas::size() const -> std::size_t
{
    return regions_.size();
}

} // namespace data
} // namespace aeon
