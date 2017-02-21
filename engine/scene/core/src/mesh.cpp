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

#include <aeon/scene/mesh.h>
#include <aeon/scene/scene_manager.h>
#include <aeon/gfx/gfx_device.h>

namespace aeon
{
namespace scene
{

mesh::mesh(scene_manager *scene_manager, const std::shared_ptr<gfx::material> &material,
           const std::vector<data::vertex_data> &vertex_data, const std::vector<std::uint32_t> &index_data,
           const std::string &name)
    : scene_object(name,
                   material->sampler_has_alpha() ? render_layer::world_geometry_alpha : render_layer::world_geometry,
                   scene_object_type::mesh, scene_manager)
    , mesh_(scene_manager->get_device().create_mesh(material))
{
    mesh_->upload_vertex_buffer(vertex_data, gfx::buffer_usage::static_usage);
    mesh_->upload_index_buffer(index_data, gfx::buffer_usage::static_usage);
}

mesh::~mesh()
{
}

void mesh::render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model, const float)
{
    mesh_->render(projection, view, model);
}

} // namespace scene
} // namespace aeon
