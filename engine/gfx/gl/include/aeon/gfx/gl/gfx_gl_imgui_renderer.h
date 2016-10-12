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

#include <aeon/gfx/gfx_imgui_renderer.h>
#include <aeon/gfx/gl/gfx_gl_window.h>
#include <aeon/gfx/gfx_frame_listener.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

class gl_imgui_renderer : public imgui_renderer, public frame_listener
{
public:
    gl_imgui_renderer();
    virtual ~gl_imgui_renderer() = default;

    void initialize(gfx_gl_window &window);


private:
    bool on_frame_begin(const float dt) override;
    bool on_frame_end(const float dt) override;

    void register_keymap();
    void register_callbacks();

    gfx_gl_window *window_;
};

} // namespace gl
} // namespace gfx
} // namespace aeon
