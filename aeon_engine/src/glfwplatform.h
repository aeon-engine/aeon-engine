/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#ifndef glfwplatform_h__
#define glfwplatform_h__

#ifdef AEON_USE_GLFW_PLATFORM

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

} // namespace platforms
} // namespace aeon

#endif // AEON_USE_GLFW_PLATFORM

#endif // glfwplatform_h__
