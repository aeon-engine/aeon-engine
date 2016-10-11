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

#include <scene/scene_object.h>
#include <glm/mat4x4.hpp>
#include <memory>

namespace aeon
{

namespace gfx
{
class viewport;
} // namespace gfx

namespace scene
{

class camera : public scene_object
{
public:
    explicit camera(scene_manager *scene_manager);
    virtual ~camera() = default;

    void render_scene(gfx::viewport &vp, float dt);

    glm::mat4 get_projection_matrix() const
    {
        return projection_matrix_;
    }

    glm::mat4 get_view_matrix() const
    {
        return view_matrix_;
    }

    glm::mat4 get_camera_matrix() const
    {
        return projection_matrix_ * view_matrix_;
    }

    void reset_view();

protected:
    glm::mat4 projection_matrix_;
    glm::mat4 view_matrix_;
};

using camera_ptr = std::shared_ptr<camera>;

} // namespace scene
} // namespace aeon
