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

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <glm/mat4x4.hpp>
#include <aeon/resources/submesh.h>
#include <aeon/utility.h>

namespace aeon
{
namespace resources
{

class mesh_node : public utility::noncopyable
{
    friend class mesh;

public:
    ~mesh_node() = default;

    auto create_child(const std::string &name, const glm::mat4 &matrix, const std::vector<submesh *> &submeshes)
        -> mesh_node &;

    auto get_children() const
    {
        return utility::container::unique_ptr_to_raw_ptr(children_);
    }

    const auto &get_submeshes() const
    {
        return submeshes_;
    }

    const auto &get_matrix() const
    {
        return matrix_;
    }

private:
    explicit mesh_node(const std::string &name, const glm::mat4 &matrix, const std::vector<submesh *> &submeshes);

    std::string name_;
    glm::mat4 matrix_;
    std::vector<std::unique_ptr<mesh_node>> children_;
    std::vector<submesh *> submeshes_;
};

} // namespace resources
} // namespace aeon
