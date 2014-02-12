#include "Aeon/Aeon.h"
#include "Aeon/GLFWApplication.h"
#include "Aeon/Game.h"
#include "Aeon/Console/Console.h"

namespace Aeon
{

GLFWApplication::GLFWApplication()
:
BaseApplication(),
m_window(NULL),
m_running(false)
{

}

GLFWApplication::~GLFWApplication()
{

}

bool GLFWApplication::__initialize()
{
	Console::info("Initializing GLFW");

	//Initialize GLFW
	if(!glfwInit())
	{
		Console::fatal("Could not initialize GLFW");
		return false;
	}

	//Create our window
	m_window = glfwCreateWindow(640, 480, "Aeon", NULL, NULL);

	if (m_window == NULL)
	{
		Console::fatal("Could not create GLFW window");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);

	return true;
}

void GLFWApplication::__cleanup()
{
	Console::info("Terminating GLFW");
	glfwTerminate();
	m_window = NULL;
}

void GLFWApplication::__run()
{
	m_running = true;

	//Make sure we don't get a huge first dt
	glfwSetTime(0);

	//While the window isn't closed and we're still running.
	while (!glfwWindowShouldClose(m_window) || m_running == false)
	{
		double dt = glfwGetTime();

		//If on_update returns false, we should stop.
		if (!m_game->on_update((float)dt))
			m_running = false;

		m_game->on_render();

		// Swap front and back buffers
		glfwSwapBuffers(m_window);

		// Poll and process events
		glfwPollEvents();

		//Reset the timer back to 0
		glfwSetTime(0);
	}

	m_running = false;
}

void GLFWApplication::__stop()
{
	m_running = false;
}

} //namespace Aeon
