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
#include <scene/scene_object.h>
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
    explicit sprite(scene_manager *scene_manager, gfx::atlas_ptr atlas, const data::atlas::region &region,
                    glm::vec2 size, int zorder);

    virtual ~sprite();

    void set_size(glm::vec2 size);
    void set_size(float width, float height);

    glm::vec2 get_size() const;

    gfx::atlas_ptr get_atlas() const;

    void set_atlas_region(const data::atlas::region &region);
    data::atlas::region get_atlas_region() const;

    void render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model, float dt) override;

    virtual void update(float /*dt*/);

protected:
    void __upload_mesh_data() const;
    void __generate_and_upload_vertex_data() const;
    void __generate_and_upload_index_data() const;

    glm::vec2 size_;

    gfx::atlas_ptr atlas_;
    data::atlas::region region_;

    gfx::mesh_ptr mesh_;
};

using sprite_ptr = std::shared_ptr<sprite>;

} // namespace scene
} // namespace aeon
