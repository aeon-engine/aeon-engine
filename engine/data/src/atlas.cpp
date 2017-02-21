/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
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
