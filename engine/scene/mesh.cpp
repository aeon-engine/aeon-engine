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

#include <scene/mesh.h>

namespace aeon
{
namespace scene
{

mesh::mesh(scene_manager *scene_manager)
    : scene_object(render_layer::world_geometry, scene_object_type::renderable, scene_manager)
{
}

mesh::~mesh()
{
}

void mesh::render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model, float dt)
{
    scene_object::render(projection, view, model, dt);
}

} // namespace scene
} // namespace aeon
