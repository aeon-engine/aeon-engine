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

#include <aeon/gfx/gfx_viewport.h>

namespace aeon
{
namespace gfx
{

viewport::viewport(gfx_camera_ptr camera, int zorder)
    : has_z_order(zorder)
    , camera_(camera)
    , rectangle_(0.0f, 0.0f, 1.0f, 1.0f)
{
}

viewport::viewport(gfx_camera_ptr camera, const common::types::rectangle<float> &rect, int zorder)
    : has_z_order(zorder)
    , camera_(camera)
    , rectangle_(rect)
{
}

void viewport::set_rectangle(const common::types::rectangle<float> &rect)
{
    rectangle_ = rect;
}

void viewport::set_camera(gfx_camera_ptr camera)
{
    camera_ = camera;
}

gfx_camera_ptr viewport::get_camera() const
{
    return camera_;
}

void viewport::update(render_target &rt, float dt)
{
    camera_->render_scene(rt, *this, dt);
}

common::types::rectangle<float> viewport::get_rectangle() const
{
    return rectangle_;
}

} // namespace gfx
} // namespace aeon
