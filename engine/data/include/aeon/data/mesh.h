/*
 * Copyright (c) 2012-2018 Robin Degen
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

#include <aeon/common/types/color.h>
#include <aeon/common/compilers.h>
#include <glm/vec3.hpp>
#include <vector>

namespace aeon
{
namespace data
{

AEON_PACK_STRUCT_PUSH(1)
struct vertex_data
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 uvw;
    common::types::color color;
    glm::vec3 tangent;
    glm::vec3 bitangent;
} AEON_PACK_STRUCT_POP(1);

using index_data_buffer = std::vector<std::uint32_t>;
using vertex_data_buffer = std::vector<vertex_data>;

} // namespace data
} // namespace aeon
