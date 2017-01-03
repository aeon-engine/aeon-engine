/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#include <gfx/gles2/gfx_gles2_shader_manager.h>
#include <gfx/gles2/gfx_gles2_shader.h>
#include <gfx/gl_common/check_gl_error.h>
#include <iostream>

namespace aeon
{
namespace gfx
{
namespace gles2
{

gfx_gles2_shader_manager::gfx_gles2_shader_manager()
    : logger_(common::logger::get_singleton(), "Gfx::GLES2::ShaderManager")
{
}

shader_ptr gfx_gles2_shader_manager::__load(resources::shader_ptr shader)
{
    GLuint vertexshader = __load_gl_shader(shader->get_vertex_source(), GL_VERTEX_SHADER);
    GLuint fragmentshader = __load_gl_shader(shader->get_fragment_source(), GL_FRAGMENT_SHADER);

    GLuint program = __link_gl_program(vertexshader, fragmentshader);

    gfx_gles2_shader_ptr s = std::make_shared<gfx_gles2_shader>();

    s->handle_ = program;
    s->projection_matrix_handle_ = glGetUniformLocation(program, "projection_matrix");
    AEON_CHECK_GL_ERROR();

    s->model_matrix_handle_ = glGetUniformLocation(program, "model_matrix");
    AEON_CHECK_GL_ERROR();

    s->view_matrix_handle_ = glGetUniformLocation(program, "view_matrix");
    AEON_CHECK_GL_ERROR();

    s->texture0_handle_ = glGetUniformLocation(program, "texture0");
    AEON_CHECK_GL_ERROR();

    AEON_LOG_TRACE(logger_) << "Uniform locations\n"
                            << "Projection Matrix: " << s->projection_matrix_handle_ << "\n"
                            << "Model Matrix: " << s->model_matrix_handle_ << "\n"
                            << "View Matrix: " << s->view_matrix_handle_ << "\n"
                            << "Texture0: " << s->texture0_handle_ << std::endl;

    return s;
}

GLuint gfx_gles2_shader_manager::__load_gl_shader(const std::string &source, GLenum type)
{
    // Create the shader object
    GLuint shader = glCreateShader(type);

    if (shader == 0)
    {
        AEON_LOG_ERROR(logger_) << "Create shader failed." << std::endl;
        throw gfx_gles2_shader_exception();
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
        throw gfx_gles2_shader_compile_exception();
    }

    return shader;
}

GLuint gfx_gles2_shader_manager::__link_gl_program(GLuint vertexshader, GLuint fragmentshader)
{
    GLuint program = glCreateProgram();
    AEON_CHECK_GL_ERROR();

    if (program == 0)
    {
        AEON_LOG_ERROR(logger_) << "Create program failed." << std::endl;
        throw gfx_gles2_shader_exception();
    }

    AEON_LOG_TRACE(logger_) << "Created program (GL handle: " << program << ")." << std::endl;

    glAttachShader(program, vertexshader);
    AEON_CHECK_GL_ERROR();
    glAttachShader(program, fragmentshader);
    AEON_CHECK_GL_ERROR();

    glBindAttribLocation(program, 0, "in_position");
    AEON_CHECK_GL_ERROR();
    glBindAttribLocation(program, 1, "in_normal");
    AEON_CHECK_GL_ERROR();
    glBindAttribLocation(program, 2, "in_uvw");
    AEON_CHECK_GL_ERROR();
    glBindAttribLocation(program, 3, "in_color");
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
        throw gfx_gles2_shader_compile_exception();
    }

    return program;
}

} // namespace gles2
} // namespace gfx
} // namespace aeon
