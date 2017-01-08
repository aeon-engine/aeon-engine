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

#include <aeon/gfx/gfx_buffer.h>
#include <glm/mat4x4.hpp>
#include <aeon/common/exception.h>
#include <aeon/data/mesh.h>
#include <memory>
#include <vector>

namespace aeon
{
namespace gfx
{

DEFINE_EXCEPTION_OBJECT(gfx_mesh_exception, aeon::common::exception, "Mesh exception.");

class mesh
{
public:
    mesh() = default;
    virtual ~mesh() = default;

    virtual void upload_vertex_buffer(const std::vector<data::vertex_data> &vertex_data,
                                      const gfx::buffer_usage usage) = 0;
    virtual void upload_index_buffer(const std::vector<std::uint16_t> &index_data, const gfx::buffer_usage usage) = 0;

    virtual void render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model) = 0;

    /*!
     * Returns true of the material used for this mesh has an alpha channel.
     */
    virtual bool has_alpha() const = 0;
};

} // namespace gfx
} // namespace aeon
