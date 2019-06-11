/*
 * Copyright (c) 2012-2018 Robin Degen
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

#pragma once

#include <aeon/gfx/gfx_frame_listener.h>
#include <aeon/gfx/gfx_viewport.h>
#include <aeon/gfx/gfx_camera.h>
#include <aeon/logger/logger.h>
#include <aeon/common/listener_subject.h>
#include <aeon/math/vector2.h>
#include <memory>
#include <vector>

namespace aeon::gfx
{

class render_target : public common::listener_subject<frame_listener>
{
public:
    render_target();
    virtual ~render_target() = default;

    /*!
     * Internal function to handle the renderig of a frame. This is called by
     * the platform interface that this render target is attached to.
     */
    auto handle_frame(float dt) -> bool;

    auto create_viewport(std::shared_ptr<gfx_camera> camera, const std::string &name, int zorder)
        -> std::shared_ptr<viewport>;

    auto create_viewport(std::shared_ptr<gfx_camera> camera, const common::types::rectangle<float> &rect,
                         const std::string &name, int zorder) -> std::shared_ptr<viewport>;

    void attach_viewport(const std::shared_ptr<viewport> &vp);

    void detach_viewport(const std::shared_ptr<viewport> &vp);

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

    /*!
     * Get the size of the render framebuffer.
     */
    virtual auto get_framebuffer_size() const -> math::vector2<float> = 0;

protected:
    virtual auto __on_frame_start(float dt) -> bool = 0;

    virtual auto __on_frame_end(float dt) -> bool = 0;

private:
    void __sort_viewports_by_zorder();

    logger::logger logger_;
    std::vector<std::shared_ptr<viewport>> viewports_;
};

} // namespace aeon::gfx
