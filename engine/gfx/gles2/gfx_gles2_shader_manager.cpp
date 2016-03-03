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

#include <gfx/gles2/gfx_gles2_shader_manager.h>
#include <gfx/gles2/gfx_gles2_shader.h>
#include <iostream>

namespace aeon
{
namespace gfx
{
namespace gles2
{

shader_manager::shader_manager()
    : logger_(common::logger::get_singleton(), "Gfx::GL::ShaderManager")
{
}

shader_ptr shader_manager::__load(resources::shader_ptr shader)
{
    GLuint vertexshader = __load_gl_shader(shader->get_vertex_source(), GL_VERTEX_SHADER);
    GLuint fragmentshader = __load_gl_shader(shader->get_fragment_source(), GL_FRAGMENT_SHADER);

    GLuint program = __link_gl_program(vertexshader, fragmentshader);

    shader_gles2_ptr s = std::make_shared<gles2::shader>();

    s->handle_ = program;
    s->projection_matrix_handle_ = glGetUniformLocation(program, "projection_matrix");
    s->model_matrix_handle_ = glGetUniformLocation(program, "model_matrix");
    s->view_matrix_handle_ = glGetUniformLocation(program, "view_matrix");
    s->texture0_handle_ = glGetUniformLocation(program, "texture0");

    AEON_LOG_TRACE(logger_) << "Uniform locations\n" <<
        "Projection Matrix: " << s->projection_matrix_handle_ << "\n" <<
        "Model Matrix: " << s->model_matrix_handle_ << "\n" <<
        "View Matrix: " << s->view_matrix_handle_ << "\n" <<
        "Texture0: " << s->texture0_handle_ << std::endl;

    return s;
}

GLuint shader_manager::__load_gl_shader(const std::string &source, GLenum type)
{
    // Create the shader object
    GLuint shader = glCreateShader(type);

    if (shader == 0)
    {
        AEON_LOG_ERROR(logger_) << "Create shader failed." << std::endl;
        throw gfx_opengl_shader_exception();
    }

    AEON_LOG_TRACE(logger_) << "Created " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
        << " shader (GL handle: " << shader << ")." << std::endl;

    const char *shader_src = source.c_str();
    glShaderSource(shader, 1, &shader_src, nullptr);

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
            glGetShaderInfoLog(shader, info_len, nullptr, info_log.data());

            AEON_LOG_ERROR(logger_) << "Error compiling shader: " << info_log.data() << std::endl;
        }
        else
        {
            AEON_LOG_ERROR(logger_) << "Unknown error compiling shader." << std::endl;
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
    {
        AEON_LOG_ERROR(logger_) << "Create program failed." << std::endl;
        throw gfx_opengl_shader_exception();
    }

    AEON_LOG_TRACE(logger_) << "Created program (GL handle: " << program << ")." << std::endl;

    glAttachShader(program, vertexshader);
    glAttachShader(program, fragmentshader);

    glBindAttribLocation(program, 0, "in_position");
    glBindAttribLocation(program, 1, "in_texture_coord");
    glBindAttribLocation(program, 2, "in_color");
    glBindAttribLocation(program, 3, "in_sprite_model_mat_col0");
    glBindAttribLocation(program, 4, "in_sprite_model_mat_col1");
    glBindAttribLocation(program, 5, "in_sprite_model_mat_col2");
    glBindAttribLocation(program, 6, "in_sprite_model_mat_col3");

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
            glGetProgramInfoLog(program, info_len, nullptr, info_log.data());

            AEON_LOG_ERROR(logger_) << "Error linking shader program: " << info_log.data() << std::endl;
        }
        else
        {
            AEON_LOG_ERROR(logger_) << "Unknown error linking shader program." << std::endl;
        }

        glDeleteProgram(program);
        throw gfx_opengl_shader_compile_exception();
    }

    return program;
}

} // namespace gles2
} // namespace gfx
} // namespace aeon
