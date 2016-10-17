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
#include <array>

struct ImDrawData;

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

    void render_draw_lists(ImDrawData *draw_data);

private:
    void __create_device_objects();
    void __create_fonts_texture();

    bool on_frame_begin(const float dt) override;
    bool on_frame_end(const float dt) override;

    void register_keymap();
    void register_callbacks();

    gfx_gl_window *window_;
    double time_;
    std::array<bool, 3> mouse_pressed_;
    float mouse_wheel_;
    GLuint font_texture_;
    int shader_handle_;
    int vert_handle_;
    int frag_handle_;
    int attrib_location_tex_;
    int attrib_location_proj_mtx_;
    int attrib_location_position_;
    int attrib_location_uv_;
    int attrib_location_color_;
    unsigned int vbo_handle_;
    unsigned int vao_handle_;
    unsigned int elements_handle_;
};

} // namespace gl
} // namespace gfx
} // namespace aeon
