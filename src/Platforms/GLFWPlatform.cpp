#include "Aeon/Aeon.h"

#ifdef AEON_USE_GLFW_PLATFORM

#include "Aeon/Root.h"
#include "Aeon/Platforms/GLFWPlatform.h"
#include "Aeon/Game.h"
#include "Aeon/Console/Console.h"

namespace Aeon
{
namespace Platforms
{

GLFW::GLFW()
:
window_(NULL),
running_(false)
{
	__initialize();
}

GLFW::~GLFW()
{
	__cleanup();
}

void GLFW::run()
{
	running_ = true;

	Root *root = Root::getSingletonPtr();

	//While the window isn't closed and we're still running.
	while (!glfwWindowShouldClose(window_) || running_ == false)
	{
		root->render();

		//Swap front and back buffers
		glfwSwapBuffers(window_);

		//Poll and process events
		glfwPollEvents();
	}

	running_ = false;
}

void GLFW::stop()
{
	running_ = false;
}

bool GLFW::__initialize()
{
	Root::create();

	Console::info("Initializing GLFW platform");

	//Initialize GLFW
	if(!glfwInit())
	{
		Console::fatal("Could not initialize GLFW");
		return false;
	}

	//Create our window
	window_ = glfwCreateWindow(1280, 780, "Aeon", NULL, NULL);

	if (window_ == NULL)
	{
		Console::fatal("Could not create GLFW window");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window_);

	return true;
}

void GLFW::__cleanup()
{
	Console::info("Terminating GLFW");
	glfwTerminate();
	window_ = NULL;
}

} /* namespace Platforms */
} /* namespace Aeon */

#endif /* AEON_USE_GLFW_PLATFORM */
