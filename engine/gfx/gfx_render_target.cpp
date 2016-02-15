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

#include <gfx/gfx_render_target.h>
#include <algorithm>

namespace aeon
{
namespace gfx
{

bool render_target::handle_frame(float dt)
{
    if (!__on_frame_start(dt))
        return false;

    // Update all listeners
    for (auto frame_listener : listeners_)
    {
        if (!frame_listener->on_frame(dt))
            return false;
    }

    // Update all viewports
    for (auto vp : viewports_)
    {
        vp->update(dt);
    }

    if (!__on_frame_end(dt))
        return false;

    return true;
}

scene::viewport_ptr render_target::create_viewport(scene::camera_ptr camera,
                                                   const common::types::rectangle<float> &rect, int zorder)
{
    scene::viewport_ptr vp = std::make_shared<scene::viewport>(camera, rect, zorder);
    viewports_.push_back(vp);

    return vp;
}

scene::viewport_ptr render_target::create_viewport(scene::camera_ptr camera, const common::types::rectangle<int> &rect,
                                                   int zorder)
{
    return create_viewport(camera, common::types::rectangle<float>(rect), zorder);
}

void render_target::detach_viewport(scene::viewport_ptr vp)
{
    viewports_.erase(std::remove(viewports_.begin(), viewports_.end(), vp), viewports_.end());
}

void render_target::remove_all_viewports()
{
    viewports_.clear();
}

} // namespace gfx
} // namespace aeon
