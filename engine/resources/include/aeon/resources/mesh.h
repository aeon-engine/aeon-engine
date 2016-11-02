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

    std::shared_ptr<mesh_resource_wrapper> get_mesh_resource_wrapper() const
    {
        return std::dynamic_pointer_cast<mesh_resource_wrapper>(get_resource_wrapper());
    }

    void add_material(const std::string &name);
    void create_submesh(const int id, const std::string &name, data::index_data_buffer &&indices,
                        data::vertex_data_buffer &&vertices, const std::string &material);

    std::string &get_material_by_id(const int id);
    submesh *get_submesh_by_id(const int id);

    std::vector<submesh *> get_submeshes() const;

    mesh_node &create_root_mesh_node(const glm::mat4 &matrix, const std::vector<submesh *> &submeshes);
    mesh_node &get_root_mesh_node() const;

private:
    aeon::logger::logger logger_;

    std::vector<std::string> materials_;
    std::vector<std::unique_ptr<submesh>> submeshes_;
    std::unique_ptr<mesh_node> root_mesh_node_;
};

} // namespace resources
} // namespace aeon
