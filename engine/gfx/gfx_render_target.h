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

    /*!
     * Add a frame listener to this render target. The on_frame event will
     * be called each frame that this render target is rendering.
     *
     * Render target does not take ownership of this pointer, so it's up to
     * the caller to keep this pointer alive, and delete it appropriately.
     */
    void attach_frame_listener(frame_listener *listener);

    /*!
     * Detach a frame listener from this render target. This will not delete
     * the frame listener, but merely detach it so events are no longer
     * triggered.
     */
    void detach_frame_listener(frame_listener *listener);

    /*!
     * Detach all frame listeners from this render target. This will not delete
     * the frame listeners, but merely detach them so events are no longer
     * triggered.
     */
    void detach_all_frame_listeners();

    /*!
     * Internal function to handle the renderig of a frame. This is called by
     * the platform interface that this render target is attached to.
     */
    bool handle_frame(double dt);

    /*!
     * Internal function to make this render target active. This is called by
     * the platform interface that this render target is attached to.
     *
     * This function must be called before attempting to render anything, since
     * the underlaying graphics driver needs to know that subsequent draw calls
     * should be executed on this render target.
     */
    virtual void make_current() = 0;

protected:
    /*!
     * This function must be implemented by the platform/gfx driver specific
     * implementation, and should do everything required to render to this render
     * target.
     *
     * This function is called from handle_frame.
     */
    virtual bool on_frame(double dt) = 0;

private:
    std::vector<frame_listener *> frame_listeners_;
};

using render_target_ptr = std::shared_ptr<render_target>;

} // namespace gfx
} // namespace aeon
