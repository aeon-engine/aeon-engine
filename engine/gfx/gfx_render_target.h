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

#include <aeon/utility.h>
#include <gfx/gfx_frame_listener.h>
#include <scene/viewport.h>
#include <scene/camera.h>
#include <memory>
#include <vector>

namespace aeon
{
namespace gfx
{

class render_target : public utility::listener_subject<frame_listener>
{
public:
    render_target() = default;
    virtual ~render_target() = default;

    /*!
     * Internal function to handle the renderig of a frame. This is called by
     * the platform interface that this render target is attached to.
     */
    bool handle_frame(float dt);

    scene::viewport_ptr create_viewport(scene::camera_ptr camera, const common::types::rectangle<float> &rect, int zorder);

    scene::viewport_ptr create_viewport(scene::camera_ptr camera, const common::types::rectangle<int> &rect, int zorder);

    void detach_viewport(scene::viewport_ptr vp);

    void remove_all_viewports();

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
    virtual bool __on_frame_start(float dt) = 0;

    virtual bool __on_frame_end(float dt) = 0;

private:
    std::vector<scene::viewport_ptr> viewports_;
};

using render_target_ptr = std::shared_ptr<render_target>;

} // namespace gfx
} // namespace aeon
