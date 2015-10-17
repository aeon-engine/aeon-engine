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

#pragma once

#include <gfx/gfx_frame_listener.h>
#include <memory>
#include <vector>

namespace aeon
{
namespace gfx
{

class render_target
{
public:
    render_target();
    virtual ~render_target();

    bool handle_pre_frame();
    bool handle_frame(double dt);
    bool handle_post_frame();

    void attach_frame_listener(frame_listener *listener);
    void detach_frame_listener(frame_listener *listener);
    void detach_all_frame_listeners();

protected:
    virtual bool pre_frame() = 0;
    virtual bool frame(double dt) = 0;
    virtual bool post_frame() = 0;

private:
    std::vector<frame_listener *> frame_listeners_;
};

using render_target_ptr = std::shared_ptr<render_target>;

} // namespace gfx
} // namespace aeon
