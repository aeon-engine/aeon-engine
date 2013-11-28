#include "AeonGLFWApplication.h"
#include "AeonGame.h"

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
	//Initialize GLFW
	if(!glfwInit())
		return false;

	//Create our window
	m_window = glfwCreateWindow(640, 480, "Aeon", NULL, NULL);

	if (m_window == NULL)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);

	return true;
}

void GLFWApplication::__cleanup()
{
	glfwTerminate();
	m_window = NULL;
}

void GLFWApplication::__run()
{
	m_running = true;

	//While the window isn't closed and we're still running.
	while (!glfwWindowShouldClose(m_window) || m_running == false)
	{
		//If on_update returns false, we should stop.
		if(!m_game->on_update(0.1f))
			m_running = false;

		m_game->on_render();

		// Swap front and back buffers
		glfwSwapBuffers(m_window);

		// Poll and process events
		glfwPollEvents();
	}

	m_running = false;
}

void GLFWApplication::__stop()
{
	m_running = false;
}

} //namespace Aeon
