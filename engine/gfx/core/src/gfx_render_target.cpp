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
        vp->update(*this, dt);
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

std::shared_ptr<viewport> render_target::create_viewport(std::shared_ptr<gfx_camera> camera, const std::string &name,
                                                         int zorder)
{
    AEON_LOG_DEBUG(logger_) << "Creating full-screen viewport '" << name << "'." << std::endl;

    std::shared_ptr<viewport> vp = std::make_shared<viewport>(camera, name, zorder);
    attach_viewport(vp);
    return vp;
}

std::shared_ptr<viewport> render_target::create_viewport(std::shared_ptr<gfx_camera> camera,
                                                         const common::types::rectangle<float> &rect,
                                                         const std::string &name, int zorder)
{
    AEON_LOG_DEBUG(logger_) << "Creating viewport '" << name << "' (" << rect << ")." << std::endl;

    std::shared_ptr<viewport> vp = std::make_shared<viewport>(camera, rect, name, zorder);
    attach_viewport(vp);
    return vp;
}

void render_target::attach_viewport(const std::shared_ptr<viewport> &vp)
{
    AEON_LOG_DEBUG(logger_) << "Attaching viewport '" << vp->get_name() << "'(" << vp->get_rectangle() << ")."
                            << std::endl;
    viewports_.push_back(vp);
    __sort_viewports_by_zorder();
}

void render_target::detach_viewport(const std::shared_ptr<viewport> &vp)
{
    AEON_LOG_DEBUG(logger_) << "Detaching viewport '" << vp->get_name() << "'." << std::endl;
    viewports_.erase(std::remove(viewports_.begin(), viewports_.end(), vp), viewports_.end());
    __sort_viewports_by_zorder();
}

void render_target::remove_all_viewports()
{
    AEON_LOG_DEBUG(logger_) << "Detaching all viewports." << std::endl;
    viewports_.clear();
}

void render_target::__sort_viewports_by_zorder()
{
    AEON_LOG_DEBUG(logger_) << "Sorting " << viewports_.size() << " viewport(s)." << std::endl;
    std::sort(viewports_.begin(), viewports_.end(),
              [](const std::shared_ptr<viewport> &a, const std::shared_ptr<viewport> &b) {
                  return a->get_zorder() < b->get_zorder();
              });
}

} // namespace gfx
} // namespace aeon
