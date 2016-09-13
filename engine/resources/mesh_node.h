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

#include <string>
#include <vector>
#include <memory>
#include <glm/mat4x4.hpp>
#include <resources/submesh.h>

namespace aeon
{
namespace resources
{

class mesh_node;
using mesh_node_ptr = std::unique_ptr<mesh_node>;

class mesh_node
{
friend class mesh;
public:
    ~mesh_node() = default;

    mesh_node &create_child(const std::string &name, const glm::mat4 &matrix, const std::vector<submesh *> &submeshes);
    std::vector<mesh_node *> get_children() const;
    std::vector<submesh *> get_submeshes() const;

    const glm::mat4 &get_matrix() const;

private:
    explicit mesh_node(const std::string &name, const glm::mat4 &matrix, const std::vector<submesh *> &submeshes);

    std::string name_;
    glm::mat4 matrix_;
    std::vector<mesh_node_ptr> children_;
    std::vector<submesh *> submeshes_;
};

} // namespace resources
} // namespace aeon
