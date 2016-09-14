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

#include <resources/mesh_node.h>
#include <aeon/utility.h>

namespace aeon
{
namespace resources
{

mesh_node::mesh_node(const std::string &name, const glm::mat4 &matrix, const std::vector<submesh *> &submeshes)
    : name_(name)
    , matrix_(matrix)
    , submeshes_(submeshes)
{
}

mesh_node &mesh_node::create_child(const std::string &name, const glm::mat4 &matrix,
                                   const std::vector<submesh *> &submeshes)
{
    mesh_node_ptr mesh = mesh_node_ptr(new mesh_node(name, matrix, submeshes));
    mesh_node *mesh_ptr = mesh.get();

    children_.emplace_back(std::move(mesh));

    return *mesh_ptr;
}

std::vector<mesh_node *> mesh_node::get_children() const
{
    return utility::container::unique_ptr_to_raw_ptr(children_);
}

std::vector<submesh *> mesh_node::get_submeshes() const
{
    return submeshes_;
}

const glm::mat4 &mesh_node::get_matrix() const
{
    return matrix_;
}

} // namespace resources
} // namespace aeon
