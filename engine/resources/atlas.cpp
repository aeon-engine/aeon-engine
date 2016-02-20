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
    , logger_(common::logger::get_singleton(), "Resources::Atlas")
    , regions_(regions)
    , names_(names)
    , material_(material)
{
    AEON_LOG_DEBUG(logger_) << "Created atlas resource based on regions." << std::endl;
}

atlas::atlas(gfx::material_ptr material, glm::vec2 sprite_size)
    : resource(nullptr)
    , logger_(common::logger::get_singleton(), "Resources::Atlas")
    , material_(material)
{
    AEON_LOG_DEBUG(logger_) << "Created atlas resource based on sprite size ("
        << sprite_size.x << "," << sprite_size.y << ")." << std::endl;
    __calculate_atlas_regions(sprite_size);
}

atlas::~atlas()
{
    AEON_LOG_DEBUG(logger_) << "Deleted atlas resource." << std::endl;
}

atlas_region atlas::get_region_by_index(int index)
{
    AEON_LOG_TRACE(logger_) << "Getting region index " << index << "." << std::endl;

    assert(regions_.size() >= index);
    return regions_.at(index);
}

atlas_region atlas::get_region_by_name(const std::string &name)
{
    AEON_LOG_TRACE(logger_) << "Getting region " << name << "." << std::endl;

    auto result = names_.find(name);

    if (result == names_.end())
    {
        AEON_LOG_ERROR(logger_) << "Region " << name << " was not found." << std::endl;
        throw atlas_exception();
    }

    return get_region_by_index(result->second);
}

gfx::material_ptr atlas::get_material() const
{
    return material_;
}

void atlas::__calculate_atlas_regions(glm::vec2 sprite_size)
{
    AEON_LOG_TRACE(logger_) << "Calculating atlas UV map regions." << std::endl;

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
