#include "Aeon/Aeon.h"

#ifdef AEON_USE_GLFW_PLATFORM

#include "Aeon/Platforms/GLFWPlatform.h"
#include "Aeon/Game.h"
#include "Aeon/Console/Console.h"

namespace Aeon
{
namespace Platforms
{

GLFW::GLFW()
:
window_(NULL)
{
}

GLFW::~GLFW()
{
}

bool GLFW::initialize()
{
	Console::info("[GLFW] Initializing GLFW platform");

	//Initialize GLFW
	if (!glfwInit())
	{
		Console::error("[GLFW] Could not initialize GLFW");
		return false;
	}

	//Create our window
	window_ = glfwCreateWindow(AEON_DEFAULT_SCREEN_WIDTH, AEON_DEFAULT_SCREEN_HEIGHT, "Aeon", NULL, NULL);

	if (window_ == NULL)
	{
		Console::error("[GLFW] Could not create GLFW window");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window_);

	return true;
}

bool GLFW::pre_frame()
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

bool GLFW::post_frame()
{
	if (!window_)
		return false;

	if (glfwWindowShouldClose(window_))
		return false;

	//Swap front and back buffers
	glfwSwapBuffers(window_);

	return true;
}

bool GLFW::dispose()
{
	Console::info("[GLFW] Terminating GLFW");

	glfwMakeContextCurrent(NULL);
	glfwTerminate();
	window_ = NULL;

	return true;
}

} /* namespace Platforms */
} /* namespace Aeon */

#endif /* AEON_USE_GLFW_PLATFORM */
