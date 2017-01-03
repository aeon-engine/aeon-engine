/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#include <aeon/resources/mesh_node.h>
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

auto mesh_node::create_child(const std::string &name, const glm::mat4 &matrix, const std::vector<submesh *> &submeshes)
    -> mesh_node &
{
    auto mesh = std::unique_ptr<mesh_node>(new mesh_node(name, matrix, submeshes));
    auto mesh_ptr = mesh.get();

    children_.emplace_back(std::move(mesh));

    return *mesh_ptr;
}

} // namespace resources
} // namespace aeon
