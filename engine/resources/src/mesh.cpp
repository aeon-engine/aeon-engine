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

#include <aeon/resources/mesh.h>

namespace aeon
{
namespace resources
{

mesh::mesh(const std::shared_ptr<resource_wrapper> &wrapper)
    : resource(wrapper)
    , logger_(common::logger::get_singleton(), "Resources::Mesh")
    , materials_()
    , submeshes_()
    , root_mesh_node_(nullptr)
{
    AEON_LOG_TRACE(logger_) << "Created empty mesh resource." << std::endl;
}

mesh::~mesh()
{
    AEON_LOG_TRACE(logger_) << "Deleted mesh resource." << std::endl;
}

void mesh::add_material(const std::string &name)
{
    materials_.push_back(name);
}

void mesh::create_submesh(const int id, const std::string &name, data::index_data_buffer &&indices,
                          data::vertex_data_buffer &&vertices, const std::string &material)
{
    submeshes_.emplace_back(std::make_unique<submesh>(id, name, std::move(indices), std::move(vertices), material));
}

auto mesh::create_root_mesh_node(const glm::mat4 &matrix, const std::vector<submesh *> &submeshes) -> mesh_node &
{
    assert(root_mesh_node_ == nullptr);
    root_mesh_node_ =
        std::unique_ptr<mesh_node>(new mesh_node(get_mesh_resource_wrapper()->get_path(), matrix, submeshes));
    return *root_mesh_node_.get();
}

auto mesh::get_root_mesh_node() const -> mesh_node &
{
    assert(root_mesh_node_ != nullptr);
    return *root_mesh_node_.get();
}

} // namespace resources
} // namespace aeon
