/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2014 Robin Degen
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

#include "stdafx.h"

#ifdef AEON_USE_GLFW_PLATFORM

namespace aeon
{
namespace platforms
{

glfw::glfw() :
    window_(nullptr)
{
}

glfw::~glfw()
{
}

bool glfw::initialize()
{
    console::info("[GLFW] Initializing GLFW platform");

    // Initialize GLFW
    if (!glfwInit())
    {
        console::error("[GLFW] Could not initialize GLFW");
        return false;
    }

    // Create our window
    window_ = glfwCreateWindow(AEON_DEFAULT_SCREEN_WIDTH, 
        AEON_DEFAULT_SCREEN_HEIGHT, "Aeon", nullptr, nullptr);

    if (window_ == nullptr)
    {
        console::error("[GLFW] Could not create GLFW window");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window_);

    return true;
}

bool glfw::pre_frame()
{
    if (!window_)
        return false;

    if (glfwWindowShouldClose(window_))
        return false;

    // Poll and process events. We do this pre-frame to reduce input latency 
    // by 1 frame
    glfwPollEvents();

    return true;
}

bool glfw::post_frame()
{
    if (!window_)
        return false;

    if (glfwWindowShouldClose(window_))
        return false;

    // Swap front and back buffers
    glfwSwapBuffers(window_);

    return true;
}

bool glfw::dispose()
{
    console::info("[GLFW] Terminating GLFW");

    glfwMakeContextCurrent(nullptr);
    glfwTerminate();
    window_ = nullptr;

    return true;
}

} /* namespace platforms */
} /* namespace aeon */

#endif /* AEON_USE_GLFW_PLATFORM */
