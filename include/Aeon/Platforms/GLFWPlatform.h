#ifndef GLFWPlatform_h__
#define GLFWPlatform_h__

#ifdef AEON_USE_GLFW_PLATFORM

#include <GLFW/glfw3.h>
#include "Aeon/Platforms/BasePlatform.h"

namespace Aeon
{
namespace Platforms
{

class GLFW : public BasePlatform
{
public:
	GLFW();
	virtual ~GLFW();

	void				run();
	void				stop();

private:
	bool				__initialize();
	void				__cleanup();
	
	GLFWwindow *		m_window;
	bool				m_running;
};

} /* namespace Platforms */
} /* namespace Aeon */

#endif /* AEON_USE_GLFW_PLATFORM */
#endif /* GLFWPlatform_h__ */
