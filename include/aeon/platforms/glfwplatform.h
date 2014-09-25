#ifndef glfwplatform_h__
#define glfwplatform_h__

#ifdef AEON_USE_GLFW_PLATFORM
#include "aeon/platforms/baseplatform.h"

namespace aeon
{
namespace platforms
{

class glfw : public base_platform
{
public:
    glfw();
    virtual ~glfw();

protected:
    virtual bool initialize();

    virtual bool pre_frame();
    virtual bool post_frame();

    virtual bool dispose();
    
    GLFWwindow *window_;
};

} /*namespace platforms */
} /*namespace aeon */

#endif /* AEON_USE_GLFW_PLATFORM */

#endif /* glfwplatform_h__ */
