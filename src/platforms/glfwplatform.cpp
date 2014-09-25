#include "aeon/aeon.h"

#ifdef AEON_USE_GLFW_PLATFORM

#include "aeon/platforms/glfwplatform.h"
#include "aeon/game.h"
#include "aeon/console/console.h"

namespace aeon
{
namespace platforms
{

glfw::glfw()
:
window_(NULL)
{
}

glfw::~glfw()
{
}

bool glfw::initialize()
{
    console::info("[GLFW] Initializing GLFW platform");

    //Initialize GLFW
    if (!glfwInit())
    {
        console::error("[GLFW] Could not initialize GLFW");
        return false;
    }

    //Create our window
    window_ = glfwCreateWindow(AEON_DEFAULT_SCREEN_WIDTH, 
        AEON_DEFAULT_SCREEN_HEIGHT, "Aeon", NULL, NULL);

    if (window_ == NULL)
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

    //Poll and process events
    //We do this pre-frame to reduce input latency by 1 frame
    glfwPollEvents();

    return true;
}

bool glfw::post_frame()
{
    if (!window_)
        return false;

    if (glfwWindowShouldClose(window_))
        return false;

    //Swap front and back buffers
    glfwSwapBuffers(window_);

    return true;
}

bool glfw::dispose()
{
    console::info("[GLFW] Terminating GLFW");

    glfwMakeContextCurrent(NULL);
    glfwTerminate();
    window_ = NULL;

    return true;
}

} //namespace platforms
} //namespace aeon

#endif /* AEON_USE_GLFW_PLATFORM */
