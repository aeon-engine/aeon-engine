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
