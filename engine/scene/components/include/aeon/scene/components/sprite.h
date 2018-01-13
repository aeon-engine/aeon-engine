/*
 * Copyright (c) 2012-2018 Robin Degen
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

#pragma once

#include <aeon/common/has_z_order.h>
#include <aeon/common/types/rectangle.h>
#include <aeon/scene/component.h>
#include <aeon/data/atlas.h>
#include <aeon/gfx/gfx_atlas.h>
#include <aeon/gfx/gfx_mesh.h>
#include <glm/vec2.hpp>
#include <memory>

namespace aeon
{
namespace scene
{

class sprite : public component, public common::has_z_order
{
public:
    explicit sprite(scene_manager &scene_manager, const std::shared_ptr<gfx::atlas> &atlas,
                    const data::atlas::region &region, const int zorder, const std::string &name = "");

    explicit sprite(scene_manager &scene_manager, const std::shared_ptr<gfx::atlas> &atlas,
                    const data::atlas::region &region, const glm::vec2 size, const int zorder,
                    const std::string &name = "");

    virtual ~sprite() = default;

    void set_size(const glm::vec2 size)
    {
        size_ = size;
    }

    void set_size(const float width, const float height)
    {
        size_ = glm::vec2(width, height);
    }

    auto get_size() const
    {
        return size_;
    }

    const auto &get_atlas() const
    {
        return atlas_;
    }

    void set_atlas_region(const data::atlas::region &region)
    {
        region_ = region;
    }

    const auto &get_atlas_region() const
    {
        return region_;
    }

    /*!
     * Get the axis aligned bounding box for this sprite. This can be used for rudimentary
     * collision detection.
     */
    auto get_axis_aligned_bounding_box() const -> common::types::rectangle<float>;

    void render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model,
                const float dt) override;

    virtual void update(const float /*dt*/);

protected:
    void __upload_mesh_data() const;
    void __generate_and_upload_vertex_data() const;
    void __generate_and_upload_index_data() const;

    glm::vec2 size_;

    std::shared_ptr<gfx::atlas> atlas_;
    data::atlas::region region_;

    std::unique_ptr<gfx::mesh> mesh_;
};

} // namespace scene
} // namespace aeon
