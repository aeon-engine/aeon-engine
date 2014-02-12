#ifndef AeonGLFWApplication_h__
#define AeonGLFWApplication_h__

#include <GLFW/glfw3.h>
#include "AeonBaseApplication.h"

namespace Aeon
{

class GLFWApplication : public BaseApplication
{
public:
	GLFWApplication();
	virtual ~GLFWApplication();

private:
	bool				__initialize();
	void				__cleanup();

	void				__run();
	void				__stop();
	
	GLFWwindow *		m_window;
	bool				m_running;
};

} //namespace Aeon

#endif // AeonGLFWApplication_h__
