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

#include <aeon/resources/resource.h>
#include <aeon/resources/exceptions.h>
#include <aeon/resources/wrappers/mesh_resource_wrapper.h>
#include <aeon/resources/mesh_node.h>
#include <aeon/resources/submesh.h>
#include <aeon/common/logger.h>
#include <string>
#include <memory>
#include <vector>

namespace aeon
{
namespace resources
{

class mesh : public resource
{
public:
    explicit mesh(const std::shared_ptr<resource_wrapper> &wrapper);

    virtual ~mesh();

    auto get_mesh_resource_wrapper() const
    {
        return std::dynamic_pointer_cast<mesh_resource_wrapper>(get_resource_wrapper());
    }

    void add_material(const std::string &name);
    void create_submesh(const int id, const std::string &name, data::index_data_buffer &&indices,
                        data::vertex_data_buffer &&vertices, const std::string &material);

    const auto &get_material_by_id(const int id)
    {
        return materials_.at(id);
    }

    auto get_submesh_by_id(const int id) -> submesh *
    {
        for (auto &submesh : submeshes_)
        {
            if (submesh->get_id() == id)
                return submesh.get();
        }

        return nullptr;
    }

    const auto &get_submeshes() const
    {
        return submeshes_;
    }

    auto create_root_mesh_node(const glm::mat4 &matrix, const std::vector<submesh *> &submeshes) -> mesh_node &;
    auto get_root_mesh_node() const -> mesh_node &;

private:
    aeon::logger::logger logger_;

    std::vector<std::string> materials_;
    std::vector<std::unique_ptr<submesh>> submeshes_;
    std::unique_ptr<mesh_node> root_mesh_node_;
};

} // namespace resources
} // namespace aeon
