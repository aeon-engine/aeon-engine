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

#include <glm/vec3.hpp>
#include <aeon/common/types/color.h>
#include <aeon/platform.h>
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
