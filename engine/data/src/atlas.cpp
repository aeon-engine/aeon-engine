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

atlas::atlas(const atlas::regions &regions)
    : regions_(regions)
{
}

void atlas::push_back(const atlas::region &region)
{
    regions_.push_back(region);
}

const atlas::regions &atlas::get_regions() const
{
    return regions_;
}

const atlas::region &atlas::at(const int index) const
{
    if (index >= regions_.size())
        throw atlas_exception();

    return regions_.at(index);
}

const atlas::region &atlas::at(const std::string &name) const
{
    for (const auto &region : regions_)
    {
        if (region.name == name)
            return region;
    }

    throw atlas_exception();
}

std::size_t atlas::size() const
{
    return regions_.size();
}

} // namespace data
} // namespace aeon
