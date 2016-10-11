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

#include <aeon/resources/submesh.h>

namespace aeon
{
namespace resources
{

submesh::submesh(const int id, const std::string &name, data::index_data_buffer &&indices,
                 data::vertex_data_buffer &&vertices, const std::string &material)
    : id_(id)
    , name_(name)
    , indices_(std::move(indices))
    , vertices_(std::move(vertices))
    , material_(material)
{
}

int submesh::get_id() const
{
    return id_;
}

std::string submesh::get_name() const
{
    return name_;
}

const data::index_data_buffer &submesh::get_index_data() const
{
    return indices_;
}

const data::vertex_data_buffer &submesh::get_vertex_data() const
{
    return vertices_;
}

const std::string &submesh::get_material() const
{
    return material_;
}

} // namespace resources
} // namespace aeon
