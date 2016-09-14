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

#include <scene/scene_object.h>
#include <gfx/gfx_mesh.h>
#include <gfx/gfx_material.h>
#include <memory>

namespace aeon
{
namespace scene
{

class mesh : public scene_object
{
public:
    explicit mesh(scene_manager *scene_manager, gfx::material_ptr material,
                  const std::vector<data::vertex_data> &vertex_data, const std::vector<std::uint16_t> &index_data);

    virtual ~mesh();

private:
    void render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model, float dt) override;

    gfx::mesh_ptr mesh_;
};

using mesh_ptr = std::shared_ptr<mesh>;

} // namespace scene
} // namespace aeon
