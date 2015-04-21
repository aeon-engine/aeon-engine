/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2014 Robin Degen
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

#ifndef shader_h__
#define shader_h__

namespace aeon
{

class shader : public resource
{
public:
    shader(resource_manager *creator, const std::string &name,
           std::uint64_t handle);
    virtual ~shader();

    void bind();

protected:
    enum class program_type
    {
        none,
        fragment,
        vertex
    };

    virtual bool __load_impl(aeon::streams::stream_ptr stream);
    virtual bool __unload_impl();
    virtual bool __finalize_impl();

    GLuint __load_shader(const std::string &source, GLenum type);
    GLuint __link_program(GLuint vertexshader, GLuint fragmentshader);

    std::string fragment_src_;
    std::string vertex_src_;

    GLuint program_;

    GLint matrix_handle_;
    GLint texture0_handle_;
    GLint color_handle_;
};

typedef std::shared_ptr<shader> shader_ptr;

} // namespace aeon

#endif // shader_h__
