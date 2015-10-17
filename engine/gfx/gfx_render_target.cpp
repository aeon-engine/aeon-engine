/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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

render_target::render_target()
{
}

render_target::~render_target()
{
}

bool render_target::handle_pre_frame()
{
    if(!pre_frame())
        return false;

    for (auto frame_listener : frame_listeners_)
    {
        if(!frame_listener->pre_frame())
            return false;
    }

    return true;
}

bool render_target::handle_frame(double dt)
{
    if(!frame(dt))
        return false;

    for (auto frame_listener : frame_listeners_)
    {
        if(!frame_listener->frame(dt))
            return false;
    }

    return true;
}

bool render_target::handle_post_frame()
{
    if(!post_frame())
        return false;

    for (auto frame_listener : frame_listeners_)
    {
        if(!frame_listener->post_frame())
            return false;
    }

    return true;
}

void render_target::attach_frame_listener(frame_listener *listener)
{
    frame_listeners_.push_back(listener);
}

void render_target::detach_frame_listener(frame_listener *listener)
{
    auto result = std::find_if(frame_listeners_.begin(), frame_listeners_.end(),
        [listener](const frame_listener *val)
        {
            return listener == val;
        }
    );

    if (result != frame_listeners_.end())
        frame_listeners_.erase(result);
}

void render_target::detach_all_frame_listeners()
{
    frame_listeners_.clear();
}

} // namespace gfx
} // namespace aeon
