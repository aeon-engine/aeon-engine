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

#include <platform/ios/platform_ios_window.h>
#include <platform/ios/platform_ios_interface.h>
#include <OpenGLES/ES2/gl.h>
#include <common/check_gl_error.h>

#import <UIKit/UIKit.h>

namespace aeon
{
namespace platform
{
namespace ios
{

platform_window::platform_window(platform_interface *interface, int width, int height, const std::string &title)
    : platform::platform_window(width, height, title)
    , logger_(common::logger::get_singleton(), "Platform::Raspberry")
    , interface_(interface)
{
    AEON_LOG_DEBUG(logger_) << "Creating OpenGL ES 2.0 context." << std::endl;

    EAGLContext *context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    [EAGLContext setCurrentContext:context];

    GLuint frame_buffer;
    glGenFramebuffers(1, &frame_buffer);
    glBindBuffer(GL_FRAMEBUFFER, frame_buffer);

    GLuint render_buffer;
    glGenRenderbuffers(1, &render_buffer);
    glBindBuffer(GL_RENDERBUFFER, render_buffer);

    glBindRenderbuffer(GL_RENDERBUFFER, frame_buffer);
}

platform_window::~platform_window()
{
}

void platform_window::make_current()
{
}

glm::vec2 platform_window::get_framebuffer_size()
{
    // TODO
    return glm::vec2(0, 0);
}

bool platform_window::__on_frame_start(float /*dt*/)
{
    make_current();

    return true;
}

bool platform_window::__on_frame_end(float /*dt*/)
{
    glFinish();
    AEON_CHECK_GL_ERROR();

    EAGLContext* context = [EAGLContext currentContext];
    [context presentRenderbuffer:GL_RENDERBUFFER];

    return true;
}

} // namespace ios
} // namespace platform
} // namespace aeon
