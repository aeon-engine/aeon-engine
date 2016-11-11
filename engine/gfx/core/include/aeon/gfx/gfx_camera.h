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

#include <glm/mat4x4.hpp>
#include <memory>

namespace aeon
{
namespace gfx
{

class viewport;
class render_target;

class gfx_camera
{
public:
    explicit gfx_camera();
    virtual ~gfx_camera() = default;

    virtual void render_scene(render_target &rt, viewport &vp, const float dt) = 0;

    const auto &get_projection_matrix() const
    {
        return projection_matrix_;
    }

    const auto &get_view_matrix() const
    {
        return view_matrix_;
    }

    auto get_camera_matrix() const
    {
        return projection_matrix_ * view_matrix_;
    }

    void reset_view();

protected:
    glm::mat4 projection_matrix_;
    glm::mat4 view_matrix_;
};

} // namespace gfx
} // namespace aeon
