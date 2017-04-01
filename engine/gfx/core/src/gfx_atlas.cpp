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

auto atlas::get_region_by_index(int index) const -> data::atlas::region
{
    AEON_LOG_TRACE(logger_) << "Getting region index " << index << "." << std::endl;
    return atlas_.at(index);
}

auto atlas::get_region_by_name(const std::string &name) const -> data::atlas::region
{
    AEON_LOG_TRACE(logger_) << "Getting region " << name << "." << std::endl;
    return atlas_.at(name);
}

auto atlas::get_material() const -> std::shared_ptr<material>
{
    return material_;
}

void atlas::__calculate_atlas_regions(glm::vec2 sprite_size)
{
    AEON_LOG_TRACE(logger_) << "Calculating atlas UV map regions." << std::endl;

    // TODO: Is the first sampler an indication of how large the atlas is?
    glm::vec2 full_size = material_->get_sampler_by_index(0)->get_size();

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
