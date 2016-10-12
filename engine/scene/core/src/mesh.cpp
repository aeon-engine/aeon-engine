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

#include <aeon/scene/mesh.h>
#include <aeon/scene/scene_manager.h>
#include <aeon/gfx/gfx_device.h>

namespace aeon
{
namespace scene
{

mesh::mesh(scene_manager *scene_manager, gfx::material_ptr material, const std::vector<data::vertex_data> &vertex_data,
           const std::vector<std::uint16_t> &index_data)
    : scene_object(render_layer::world_geometry, scene_object_type::mesh, scene_manager)
    , mesh_(scene_manager->get_device().create_mesh(material))
{
    mesh_->upload_vertex_buffer(vertex_data, gfx::buffer_usage::static_usage);
    mesh_->upload_index_buffer(index_data, gfx::buffer_usage::static_usage);
}

mesh::~mesh()
{
}

void mesh::render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model, float)
{
    mesh_->render(projection, view, model);
}

} // namespace scene
} // namespace aeon