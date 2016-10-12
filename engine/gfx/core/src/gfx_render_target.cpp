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

#include <aeon/gfx/gfx_render_target.h>
#include <algorithm>

namespace aeon
{
namespace gfx
{

render_target::render_target()
    : logger_(common::logger::get_singleton(), "Gfx::RenderTarget")
{
}

bool render_target::handle_frame(float dt)
{
    if (!__on_frame_start(dt))
        return false;

    // Update all listeners
    for (auto frame_listener : listeners_)
    {
        if (!frame_listener->on_frame_begin(dt))
            return false;
    }

    // Update all viewports
    for (auto vp : viewports_)
    {
        vp->update(dt);
    }

    // Update all listeners
    for (auto frame_listener : listeners_)
    {
        if (!frame_listener->on_frame_end(dt))
            return false;
    }

    if (!__on_frame_end(dt))
        return false;

    return true;
}

viewport_ptr render_target::create_viewport(gfx::gfx_camera_ptr camera, int zorder)
{
    glm::vec2 backbuffer_size = get_framebuffer_size();
    return create_viewport(camera, aeon::common::types::rectangle<float>(0, 0, backbuffer_size.x, backbuffer_size.y),
                           zorder);
}

viewport_ptr render_target::create_viewport(gfx::gfx_camera_ptr camera, const common::types::rectangle<float> &rect,
                                            int zorder)
{
    AEON_LOG_DEBUG(logger_) << "Creating viewport (" << rect << ")." << std::endl;

    viewport_ptr vp = std::make_shared<viewport>(camera, rect, zorder);
    viewports_.push_back(vp);

    return vp;
}

viewport_ptr render_target::create_viewport(gfx::gfx_camera_ptr camera, const common::types::rectangle<int> &rect,
                                            int zorder)
{
    return create_viewport(camera, common::types::rectangle<float>(rect), zorder);
}

void render_target::detach_viewport(viewport_ptr vp)
{
    AEON_LOG_DEBUG(logger_) << "Detaching viewport." << std::endl;
    viewports_.erase(std::remove(viewports_.begin(), viewports_.end(), vp), viewports_.end());
}

void render_target::remove_all_viewports()
{
    AEON_LOG_DEBUG(logger_) << "Detaching all viewports." << std::endl;
    viewports_.clear();
}

} // namespace gfx
} // namespace aeon