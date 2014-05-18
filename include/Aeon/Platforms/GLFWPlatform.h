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

protected:
	virtual bool		initialize();

	virtual bool		pre_frame();
	virtual bool		post_frame();

	virtual bool		dispose();
	
	GLFWwindow *		window_;
};

} /* namespace Platforms */
} /* namespace Aeon */

#endif /* AEON_USE_GLFW_PLATFORM */
#endif /* GLFWPlatform_h__ */
