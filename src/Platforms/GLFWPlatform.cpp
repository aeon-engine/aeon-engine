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
m_window(NULL),
m_running(false)
{
	__initialize();
}

GLFW::~GLFW()
{
	__cleanup();
}

void GLFW::run()
{
	m_running = true;

	Root *root = Root::getSingletonPtr();

	//While the window isn't closed and we're still running.
	while (!glfwWindowShouldClose(m_window) || m_running == false)
	{
		root->render();

		//Swap front and back buffers
		glfwSwapBuffers(m_window);

		//Poll and process events
		glfwPollEvents();
	}

	m_running = false;
}

void GLFW::stop()
{
	m_running = false;
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
	m_window = glfwCreateWindow(1280, 780, "Aeon", NULL, NULL);

	if (m_window == NULL)
	{
		Console::fatal("Could not create GLFW window");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);

	return true;
}

void GLFW::__cleanup()
{
	Console::info("Terminating GLFW");
	glfwTerminate();
	m_window = NULL;
}

} /* namespace Platforms */
} /* namespace Aeon */

#endif /* AEON_USE_GLFW_PLATFORM */
