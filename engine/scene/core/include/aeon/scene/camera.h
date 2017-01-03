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

#include <aeon/gfx/gfx_camera.h>
#include <aeon/scene/scene_object.h>
#include <memory>

namespace aeon
{

namespace gfx
{
class viewport;
class render_target;
} // namespace gfx

namespace scene
{

class camera : public gfx::gfx_camera, public scene_object
{
public:
    explicit camera(scene_manager *scene_manager);
    virtual ~camera() = default;

    void render_scene(gfx::render_target &rt, gfx::viewport &vp, const float dt) override;
};

} // namespace scene
} // namespace aeon
