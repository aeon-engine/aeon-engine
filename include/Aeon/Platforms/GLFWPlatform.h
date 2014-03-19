#ifndef GLFWPlatform_h__
#define GLFWPlatform_h__

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

#endif // GLFWPlatform_h__
