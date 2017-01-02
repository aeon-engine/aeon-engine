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

#pragma once

#include <aeon/common/has_z_order.h>
#include <aeon/common/types/rectangle.h>
#include <aeon/scene/scene_object.h>
#include <aeon/data/atlas.h>
#include <aeon/gfx/gfx_atlas.h>
#include <aeon/gfx/gfx_mesh.h>
#include <glm/vec2.hpp>
#include <memory>

namespace aeon
{
namespace scene
{

class sprite : public scene_object, public common::has_z_order
{
public:
    explicit sprite(scene_manager *scene_manager, const std::shared_ptr<gfx::atlas> &atlas,
                    const data::atlas::region &region, const int zorder);

    explicit sprite(scene_manager *scene_manager, const std::shared_ptr<gfx::atlas> &atlas,
                    const data::atlas::region &region, const glm::vec2 size, const int zorder);

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
