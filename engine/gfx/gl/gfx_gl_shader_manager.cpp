/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
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

#include <gfx/gl/gfx_gl_shader_manager.h>
#include <gfx/gl/gfx_gl_shader.h>
#include <iostream>

namespace aeon
{
namespace gfx
{
namespace gl
{

shader_ptr shader_manager::__load(resources::shader_ptr shader)
{
    GLuint vertexshader = __load_gl_shader(shader->get_vertex_source(), GL_VERTEX_SHADER);
    GLuint fragmentshader = __load_gl_shader(shader->get_fragment_source(), GL_FRAGMENT_SHADER);

    GLuint program = __link_gl_program(vertexshader, fragmentshader);

    glBindFragDataLocation(program, 0, "output_color");

    shader_gl_ptr s = std::make_shared<gl::shader>();

    s->handle_ = program;
    s->projection_matrix_handle_ = glGetUniformLocation(program, "projection_matrix");
    s->model_matrix_handle_ = glGetUniformLocation(program, "model_matrix");
    s->view_matrix_handle_ = glGetUniformLocation(program, "view_matrix");
    s->texture0_handle_ = glGetUniformLocation(program, "texture0");

    return s;
}

GLuint shader_manager::__load_gl_shader(const std::string &source, GLenum type)
{
    // Create the shader object
    GLuint shader = glCreateShader(type);

    if (shader == 0)
        throw gfx_opengl_shader_exception();

    const char *shader_src = source.c_str();
    glShaderSource(shader, 1, &shader_src, NULL);

    glCompileShader(shader);

    // Check the compile status
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (!status)
    {
        GLint info_len = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);

        if (info_len > 1)
        {
            std::vector<char> info_log(info_len);
            glGetShaderInfoLog(shader, info_len, NULL, info_log.data());

            // TODO: console logging
            std::cerr << "Error compiling shader: " << std::endl << info_log.data() << std::endl;
        }

        glDeleteShader(shader);
        throw gfx_opengl_shader_compile_exception();
    }

    return shader;
}

GLuint shader_manager::__link_gl_program(GLuint vertexshader, GLuint fragmentshader)
{
    GLuint program = glCreateProgram();

    if (program == 0)
        throw gfx_opengl_shader_exception();

    glAttachShader(program, vertexshader);
    glAttachShader(program, fragmentshader);

    glLinkProgram(program);

    // Check the link status
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (!status)
    {
        GLint info_len = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_len);

        if (info_len > 1)
        {
            std::vector<char> info_log(info_len);
            glGetProgramInfoLog(program, info_len, NULL, info_log.data());

            // TODO: console logging
            std::cerr << "Error linking shader program: " << std::endl << info_log.data() << std::endl;
        }

        glDeleteProgram(program);
        throw gfx_opengl_shader_compile_exception();
    }

    return program;
}

} // namespace gl
} // namespace gfx
} // namespace aeon
