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

#include <aeon/gfx/gfx_atlas.h>
#include <aeon/gfx/gfx_texture.h>

namespace aeon
{
namespace gfx
{

atlas::atlas(const std::shared_ptr<material> &material, const data::atlas &atlas)
    : logger_(common::logger::get_singleton(), "Gfx::Atlas")
    , material_(material)
    , atlas_(atlas)
{
}

atlas::atlas(const std::shared_ptr<material> &material, glm::vec2 sprite_size)
    : logger_(common::logger::get_singleton(), "Gfx::Atlas")
    , material_(material)
    , atlas_()
{
    __calculate_atlas_regions(sprite_size);
}

std::shared_ptr<material> atlas::get_material() const
{
    return material_;
}

data::atlas::region atlas::get_region_by_index(int index)
{
    AEON_LOG_TRACE(logger_) << "Getting region index " << index << "." << std::endl;
    return atlas_.at(index);
}

data::atlas::region atlas::get_region_by_name(const std::string &name)
{
    AEON_LOG_TRACE(logger_) << "Getting region " << name << "." << std::endl;
    return atlas_.at(name);
}

void atlas::__calculate_atlas_regions(glm::vec2 sprite_size)
{
    AEON_LOG_TRACE(logger_) << "Calculating atlas UV map regions." << std::endl;

    // TODO: find a better way for this...
    glm::vec2 full_size = material_->get_sampler("texture0")->get_size();

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

            atlas_.push_back(data::atlas::region{left, top, right, bottom, sprite_size.x, sprite_size.y});
        }
    }
}

} // namespace gfx
} // namespace aeon
