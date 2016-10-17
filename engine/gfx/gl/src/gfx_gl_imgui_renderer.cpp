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

#include <GL/glew.h>

#include <aeon/gfx/gl/gfx_gl_imgui_renderer.h>
#include <aeon/platform.h>
#include <imgui.h>
#include <cstddef>

#if (AEON_PLATFORM_OS_WINDOWS)
#undef APIENTRY
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3native.h>
#endif

namespace aeon
{
namespace gfx
{
namespace gl
{

static void imgui_renderer_render_draw_lists(ImDrawData *draw_data)
{
    ImGuiIO &io = ImGui::GetIO();
    gl_imgui_renderer *renderer = static_cast<gl_imgui_renderer*>(io.UserData);

    assert(renderer != nullptr);

    renderer->render_draw_lists(draw_data);
}

static void imgui_renderer_set_clipboard_text(const char *text)
{
    (void)text;
}

static const char *imgui_renderer_get_clipboard_text()
{
    return "Hello";
}

gl_imgui_renderer::gl_imgui_renderer()
    : window_(nullptr)
    , time_(0)
    , mouse_pressed_({{false, false, false}})
    , mouse_wheel_(0)
    , font_texture_(0)
    , shader_handle_(0)
    , vert_handle_(0)
    , frag_handle_(0)
    , attrib_location_tex_(0)
    , attrib_location_proj_mtx_(0)
    , attrib_location_position_(0)
    , attrib_location_uv_(0)
    , attrib_location_color_(0)
    , vbo_handle_(0)
    , vao_handle_(0)
    , elements_handle_(0)
    , show_test_window_(true)
{
}

void gl_imgui_renderer::initialize(gfx_gl_window &window)
{
    window_ = &window;

    ImGuiIO &io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;

    register_keymap();
    register_callbacks();
}

void gl_imgui_renderer::render_draw_lists(ImDrawData *draw_data)
{
    // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer
    // coordinates)
    ImGuiIO &io = ImGui::GetIO();
    int fb_width = static_cast<int>(io.DisplaySize.x * io.DisplayFramebufferScale.x);
    int fb_height = static_cast<int>(io.DisplaySize.y * io.DisplayFramebufferScale.y);
    if (fb_width == 0 || fb_height == 0)
        return;
    draw_data->ScaleClipRects(io.DisplayFramebufferScale);

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);

    // Setup viewport, orthographic projection matrix
    glViewport(0, 0, static_cast<GLsizei>(fb_width), static_cast<GLsizei>(fb_height));
    const float ortho_projection[4][4] = {
        {2.0f / io.DisplaySize.x, 0.0f, 0.0f, 0.0f},
        {0.0f, 2.0f / -io.DisplaySize.y, 0.0f, 0.0f},
        {0.0f, 0.0f, -1.0f, 0.0f},
        {-1.0f, 1.0f, 0.0f, 1.0f},
    };

    glUseProgram(shader_handle_);
    glUniform1i(attrib_location_tex_, 0);
    glUniformMatrix4fv(attrib_location_proj_mtx_, 1, GL_FALSE, &ortho_projection[0][0]);
    glBindVertexArray(vao_handle_);

    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
        const ImDrawList *cmd_list = draw_data->CmdLists[n];
        const ImDrawIdx *idx_buffer_offset = nullptr;

        glBindBuffer(GL_ARRAY_BUFFER, vbo_handle_);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(cmd_list->VtxBuffer.Size) * sizeof(ImDrawVert),
                     static_cast<GLvoid *>(cmd_list->VtxBuffer.Data), GL_STREAM_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements_handle_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(cmd_list->IdxBuffer.Size) * sizeof(ImDrawIdx),
                     static_cast<GLvoid *>(cmd_list->IdxBuffer.Data), GL_STREAM_DRAW);

        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
        {
            const ImDrawCmd *pcmd = &cmd_list->CmdBuffer[cmd_i];
            if (pcmd->UserCallback)
            {
                pcmd->UserCallback(cmd_list, pcmd);
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(reinterpret_cast<intptr_t>(pcmd->TextureId)));
                glScissor(static_cast<int>(pcmd->ClipRect.x), static_cast<int>(fb_height - pcmd->ClipRect.w),
                          static_cast<int>(pcmd->ClipRect.z - pcmd->ClipRect.x),
                          static_cast<int>(pcmd->ClipRect.w - pcmd->ClipRect.y));
                glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(pcmd->ElemCount),
                               sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer_offset);
            }
            idx_buffer_offset += pcmd->ElemCount;
        }
    }

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void gl_imgui_renderer::__create_device_objects()
{
    // Backup GL state
    GLint last_texture, last_array_buffer, last_vertex_array;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);

    const GLchar *vertex_shader = "#version 330\n"
                                  "uniform mat4 ProjMtx;\n"
                                  "in vec2 Position;\n"
                                  "in vec2 UV;\n"
                                  "in vec4 Color;\n"
                                  "out vec2 Frag_UV;\n"
                                  "out vec4 Frag_Color;\n"
                                  "void main()\n"
                                  "{\n"
                                  "	Frag_UV = UV;\n"
                                  "	Frag_Color = Color;\n"
                                  "	gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
                                  "}\n";

    const GLchar *fragment_shader = "#version 330\n"
                                    "uniform sampler2D Texture;\n"
                                    "in vec2 Frag_UV;\n"
                                    "in vec4 Frag_Color;\n"
                                    "out vec4 Out_Color;\n"
                                    "void main()\n"
                                    "{\n"
                                    "	Out_Color = Frag_Color * texture( Texture, Frag_UV.st);\n"
                                    "}\n";

    shader_handle_ = glCreateProgram();
    vert_handle_ = glCreateShader(GL_VERTEX_SHADER);
    frag_handle_ = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vert_handle_, 1, &vertex_shader, 0);
    glShaderSource(frag_handle_, 1, &fragment_shader, 0);
    glCompileShader(vert_handle_);
    glCompileShader(frag_handle_);
    glAttachShader(shader_handle_, vert_handle_);
    glAttachShader(shader_handle_, frag_handle_);
    glLinkProgram(shader_handle_);

    attrib_location_tex_ = glGetUniformLocation(shader_handle_, "Texture");
    attrib_location_proj_mtx_ = glGetUniformLocation(shader_handle_, "ProjMtx");
    attrib_location_position_ = glGetAttribLocation(shader_handle_, "Position");
    attrib_location_uv_ = glGetAttribLocation(shader_handle_, "UV");
    attrib_location_color_ = glGetAttribLocation(shader_handle_, "Color");

    glGenBuffers(1, &vbo_handle_);
    glGenBuffers(1, &elements_handle_);

    glGenVertexArrays(1, &vao_handle_);
    glBindVertexArray(vao_handle_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_handle_);
    glEnableVertexAttribArray(attrib_location_position_);
    glEnableVertexAttribArray(attrib_location_uv_);
    glEnableVertexAttribArray(attrib_location_color_);

    glVertexAttribPointer(attrib_location_position_, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert),
                          reinterpret_cast<GLvoid *>(offsetof(ImDrawVert, pos)));
    glVertexAttribPointer(attrib_location_uv_, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert),
                          reinterpret_cast<GLvoid *>(offsetof(ImDrawVert, uv)));
    glVertexAttribPointer(attrib_location_color_, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert),
                          reinterpret_cast<GLvoid *>(offsetof(ImDrawVert, col)));

    __create_fonts_texture();

    // Restore modified GL state
    glBindTexture(GL_TEXTURE_2D, last_texture);
    glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
    glBindVertexArray(last_vertex_array);
}

void gl_imgui_renderer::__create_fonts_texture()
{
    // Build texture atlas
    ImGuiIO &io = ImGui::GetIO();
    unsigned char *pixels;
    int width, height;

    // TODO: Could be optimized to not load full rgb8
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    GLint last_texture;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
    glGenTextures(1, &font_texture_);
    glBindTexture(GL_TEXTURE_2D, font_texture_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    // Store our identifier
    io.Fonts->TexID = reinterpret_cast<void *>(static_cast<intptr_t>(font_texture_));

    // Restore state
    glBindTexture(GL_TEXTURE_2D, last_texture);
}

bool gl_imgui_renderer::on_frame_begin(const float dt)
{
    if (!font_texture_)
        __create_device_objects();

    ImGuiIO &io = ImGui::GetIO();
    GLFWwindow *window = window_->get_glfw_window_ptr();

    // Setup display size (every frame to accommodate for window resizing)
    int w, h;
    int display_w, display_h;
    glfwGetWindowSize(window, &w, &h);
    glfwGetFramebufferSize(window, &display_w, &display_h);
    io.DisplaySize = ImVec2(static_cast<float>(w), static_cast<float>(h));
    io.DisplayFramebufferScale =
        ImVec2(w > 0 ? (static_cast<float>(display_w) / w) : 0, h > 0 ? (static_cast<float>(display_h) / h) : 0);

    // Setup time step
    io.DeltaTime = dt;

    // Setup inputs
    // (we already got mouse wheel, keyboard keys & characters from glfw callbacks polled in glfwPollEvents())
    if (glfwGetWindowAttrib(window, GLFW_FOCUSED))
    {
        double mouse_x, mouse_y;
        glfwGetCursorPos(window, &mouse_x, &mouse_y);
        io.MousePos = ImVec2(
            static_cast<float>(mouse_x),
            static_cast<float>(
                mouse_y)); // Mouse position in screen coordinates (set to -1,-1 if no mouse / on another screen, etc.)
    }
    else
    {
        io.MousePos = ImVec2(-1, -1);
    }

    for (int i = 0; i < 3; i++)
    {
        io.MouseDown[i] = mouse_pressed_[i] ||
                          glfwGetMouseButton(window, i) != 0; // If a mouse press event came, always pass it as "mouse
                                                              // held this frame", so we don't miss click-release events
                                                              // that are shorter than 1 frame.
        mouse_pressed_[i] = false;
    }

    io.MouseWheel = mouse_wheel_;
    mouse_wheel_ = 0.0f;

    // Hide OS mouse cursor if ImGui is drawing it
    glfwSetInputMode(window, GLFW_CURSOR, io.MouseDrawCursor ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);

    // Start the frame
    ImGui::NewFrame();

    // Update all listeners
    for (auto ui_listener : listeners_)
    {
        ui_listener->on_render_ui();
    }

    // HACK HACK
    ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
    ImGui::ShowTestWindow(&show_test_window_);

    return true;
}

bool gl_imgui_renderer::on_frame_end(const float)
{
    glm::vec2 framebuffer_size = window_->get_framebuffer_size();
    glViewport(0, 0, static_cast<GLsizei>(framebuffer_size.x), static_cast<GLsizei>(framebuffer_size.y));
    ImGui::Render();
    return true;
}

void gl_imgui_renderer::register_keymap()
{
    ImGuiIO &io = ImGui::GetIO();
    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
}

void gl_imgui_renderer::register_callbacks()
{
    ImGuiIO &io = ImGui::GetIO();

    io.UserData = this;

    io.RenderDrawListsFn = imgui_renderer_render_draw_lists;
    io.SetClipboardTextFn = imgui_renderer_set_clipboard_text;
    io.GetClipboardTextFn = imgui_renderer_get_clipboard_text;

#if (AEON_PLATFORM_OS_WINDOWS)
    io.ImeWindowHandle = glfwGetWin32Window(window_->get_glfw_window_ptr());
#endif
}

} // namespace gl
} // namespace gfx
} // namespace aeon
