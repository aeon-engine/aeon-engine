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

atlas::atlas(gfx::material_ptr material, glm::vec2 sprite_size)
    : resource(nullptr)
    , material_(material)
{
    __calculate_atlas_regions(sprite_size);
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

void atlas::__calculate_atlas_regions(glm::vec2 sprite_size)
{
    glm::vec2 full_size = material_->get_texture()->get_size();

    int sprites_per_row = static_cast<int>(full_size.x / sprite_size.x);
    int sprites_per_column = static_cast<int>(full_size.y / sprite_size.y);

    for (int column = 0; column < sprites_per_column; ++column)
    {
        for (int row = 0; row < sprites_per_row; ++row)
        {
            int left_offset = row * static_cast<int>(sprite_size.x);
            int top_offset = column * static_cast<int>(sprite_size.y);

            float left = static_cast<float>(left_offset) / static_cast<float>(full_size.x);
            float right = static_cast<float>(left_offset + sprite_size.x) / static_cast<float>(full_size.x);
            float top = static_cast<float>(top_offset) / static_cast<float>(full_size.y);
            float bottom = static_cast<float>(top_offset + sprite_size.y) / static_cast<float>(full_size.y);

            atlas_region region(left, top, right, bottom, sprite_size);
            regions_.push_back(region);
        }
    }
}

} // namespace resources
} // namespace aeon
