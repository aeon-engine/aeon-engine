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

#include <resources/atlas.h>
#include <cassert>

namespace aeon
{
namespace resources
{

atlas::atlas(resource_wrapper_ptr wrapper, gfx::material_ptr material, const atlas_regions &regions,
             const atlas_region_names &names)
    : resource(wrapper)
    , regions_(regions)
    , names_(names)
    , material_(material)
{
}

atlas_region atlas::get_region_by_index(int index)
{
    assert(regions_.size() >= index);
    return regions_.at(index);
}

atlas_region atlas::get_region_by_name(const std::string &name)
{
    auto result = names_.find(name);

    if (result == names_.end())
        throw atlas_exception();

    return get_region_by_index(result->second);
}

gfx::material_ptr atlas::get_material() const
{
    return material_;
}

} // namespace resources
} // namespace aeon
