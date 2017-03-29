/*
 * Copyright (c) 2012-2017 Robin Degen
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

auto render_target::handle_frame(float dt) -> bool
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

auto render_target::create_viewport(std::shared_ptr<gfx_camera> camera, const std::string &name, int zorder)
    -> std::shared_ptr<viewport>
{
    AEON_LOG_DEBUG(logger_) << "Creating full-screen viewport '" << name << "'." << std::endl;

    std::shared_ptr<viewport> vp = std::make_shared<viewport>(camera, name, zorder);
    attach_viewport(vp);
    return vp;
}

auto render_target::create_viewport(std::shared_ptr<gfx_camera> camera, const common::types::rectangle<float> &rect,
                                    const std::string &name, int zorder) -> std::shared_ptr<viewport>
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
