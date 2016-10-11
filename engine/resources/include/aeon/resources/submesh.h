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

#include <aeon/data/mesh.h>
#include <string>
#include <memory>

namespace aeon
{
namespace resources
{

class submesh
{
public:
    explicit submesh(const int id, const std::string &name, data::index_data_buffer &&indices,
                     data::vertex_data_buffer &&vertices, const std::string &material);
    ~submesh() = default;

    int get_id() const;
    std::string get_name() const;

    const data::index_data_buffer &get_index_data() const;
    const data::vertex_data_buffer &get_vertex_data() const;

    const std::string &get_material() const;

private:
    int id_;
    std::string name_;

    data::index_data_buffer indices_;
    data::vertex_data_buffer vertices_;

    std::string material_;
};

using submesh_ptr = std::unique_ptr<submesh>;

} // namespace resources
} // namespace aeon
