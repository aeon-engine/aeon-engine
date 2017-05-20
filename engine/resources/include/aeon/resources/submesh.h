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

#include <aeon/data/mesh.h>
#include <string>

namespace aeon
{
namespace resources
{

class submesh
{
public:
    explicit submesh(const int id, const std::string &name, data::index_data_buffer &&indices,
                     data::vertex_data_buffer &&vertices, const std::string &material)
        : id_(id)
        , name_(name)
        , indices_(std::move(indices))
        , vertices_(std::move(vertices))
        , material_(material)
    {
    }

    ~submesh() = default;

    auto get_id() const
    {
        return id_;
    }

    const auto &get_name() const
    {
        return name_;
    }

    const auto &get_index_data() const
    {
        return indices_;
    }

    const auto &get_vertex_data() const
    {
        return vertices_;
    }

    const auto &get_material() const
    {
        return material_;
    }

private:
    int id_;
    std::string name_;

    data::index_data_buffer indices_;
    data::vertex_data_buffer vertices_;

    std::string material_;
};

} // namespace resources
} // namespace aeon
