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

#include <resources/mesh.h>
#include <aeon/utility.h>

namespace aeon
{
namespace resources
{

mesh::mesh(resource_wrapper_ptr wrapper)
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
    submeshes_.emplace_back(
        std::move(submesh_ptr(new submesh(id, name, std::move(indices), std::move(vertices), material))));
}

std::string &mesh::get_material_by_id(const int id)
{
    return materials_.at(id);
}

submesh *mesh::get_submesh_by_id(const int id)
{
    for (auto &submesh : submeshes_)
    {
        if (submesh->get_id() == id)
            return submesh.get();
    }

    return nullptr;
}

std::vector<submesh *> mesh::get_submeshes() const
{
    return utility::container::unique_ptr_to_raw_ptr(submeshes_);
}

mesh_node &mesh::create_root_mesh_node(const glm::mat4 &matrix, const std::vector<submesh *> &submeshes)
{
    assert(root_mesh_node_ == nullptr);
    root_mesh_node_ = mesh_node_ptr(new mesh_node(get_mesh_resource_wrapper()->get_path(), matrix, submeshes));
    return *root_mesh_node_.get();
}

mesh_node &mesh::get_root_mesh_node() const
{
    assert(root_mesh_node_ != nullptr);
    return *root_mesh_node_.get();
}

} // namespace resources
} // namespace aeon
