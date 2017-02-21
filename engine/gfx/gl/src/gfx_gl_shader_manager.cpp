/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <aeon/gfx/gl/gfx_gl_shader_manager.h>
#include <aeon/gfx/gl/gfx_gl_shader.h>
#include <iostream>
#include <aeon/gfx/gl_common/check_gl_error.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

gfx_gl_shader_manager::gfx_gl_shader_manager()
    : logger_(common::logger::get_singleton(), "Gfx::GL::ShaderManager")
{
}

std::shared_ptr<shader> gfx_gl_shader_manager::create(const data::shader &shader_data)
{
    GLuint vertexshader = __load_gl_shader(shader_data.get_vertex_source(), GL_VERTEX_SHADER);
    GLuint fragmentshader = __load_gl_shader(shader_data.get_fragment_source(), GL_FRAGMENT_SHADER);

    GLuint program = __link_gl_program(vertexshader, fragmentshader);

    glBindFragDataLocation(program, 0, "output_color");
    AEON_CHECK_GL_ERROR();

    std::shared_ptr<gfx_gl_shader> s = std::make_shared<gfx_gl_shader>();

    s->handle_ = program;
    s->projection_matrix_handle_ = glGetUniformLocation(program, "projection_matrix");
    AEON_CHECK_GL_ERROR();

    s->model_matrix_handle_ = glGetUniformLocation(program, "model_matrix");
    AEON_CHECK_GL_ERROR();

    s->view_matrix_handle_ = glGetUniformLocation(program, "view_matrix");
    AEON_CHECK_GL_ERROR();

    AEON_LOG_TRACE(logger_) << "Uniform locations\n"
                            << "Projection Matrix: " << s->projection_matrix_handle_ << "\n"
                            << "Model Matrix: " << s->model_matrix_handle_ << "\n"
                            << "View Matrix: " << s->view_matrix_handle_ << std::endl;

    return s;
}

GLuint gfx_gl_shader_manager::__load_gl_shader(const std::string &source, GLenum type) const
{
    // Create the shader object
    GLuint shader = glCreateShader(type);
    AEON_CHECK_GL_ERROR();

    if (shader == 0)
    {
        AEON_LOG_ERROR(logger_) << "Create shader failed." << std::endl;
        throw gfx_opengl_shader_exception();
    }

    AEON_LOG_TRACE(logger_) << "Created " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                            << " shader (GL handle: " << shader << ")." << std::endl;

    const char *shader_src = source.c_str();
    glShaderSource(shader, 1, &shader_src, nullptr);
    AEON_CHECK_GL_ERROR();

    glCompileShader(shader);
    AEON_CHECK_GL_ERROR();

    // Check the compile status
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    AEON_CHECK_GL_ERROR();

    if (!status)
    {
        GLint info_len = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);
        AEON_CHECK_GL_ERROR();

        if (info_len > 1)
        {
            std::vector<char> info_log(info_len);
            glGetShaderInfoLog(shader, info_len, nullptr, info_log.data());
            AEON_CHECK_GL_ERROR();

            AEON_LOG_ERROR(logger_) << "Error compiling shader: " << info_log.data() << std::endl;
        }
        else
        {
            AEON_LOG_ERROR(logger_) << "Unknown error compiling shader." << std::endl;
        }

        glDeleteShader(shader);
        AEON_CHECK_GL_ERROR();
        throw gfx_opengl_shader_compile_exception();
    }

    return shader;
}

GLuint gfx_gl_shader_manager::__link_gl_program(GLuint vertexshader, GLuint fragmentshader) const
{
    GLuint program = glCreateProgram();
    AEON_CHECK_GL_ERROR();

    if (program == 0)
    {
        AEON_LOG_ERROR(logger_) << "Create program failed." << std::endl;
        throw gfx_opengl_shader_exception();
    }

    AEON_LOG_TRACE(logger_) << "Created program (GL handle: " << program << ")." << std::endl;

    glAttachShader(program, vertexshader);
    AEON_CHECK_GL_ERROR();

    glAttachShader(program, fragmentshader);
    AEON_CHECK_GL_ERROR();

    glLinkProgram(program);
    AEON_CHECK_GL_ERROR();

    // Check the link status
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    AEON_CHECK_GL_ERROR();

    if (!status)
    {
        GLint info_len = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_len);
        AEON_CHECK_GL_ERROR();

        if (info_len > 1)
        {
            std::vector<char> info_log(info_len);
            glGetProgramInfoLog(program, info_len, nullptr, info_log.data());
            AEON_CHECK_GL_ERROR();

            AEON_LOG_ERROR(logger_) << "Error linking shader program: " << info_log.data() << std::endl;
        }
        else
        {
            AEON_LOG_ERROR(logger_) << "Unknown error linking shader program." << std::endl;
        }

        glDeleteProgram(program);
        AEON_CHECK_GL_ERROR();
        throw gfx_opengl_shader_compile_exception();
    }

    return program;
}

} // namespace gl
} // namespace gfx
} // namespace aeon
