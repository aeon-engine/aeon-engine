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
    submeshes_.emplace_back(
        std::move(std::make_unique<submesh>(id, name, std::move(indices), std::move(vertices), material)));
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
