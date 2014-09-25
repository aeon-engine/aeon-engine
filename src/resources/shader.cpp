#include "aeon/aeon.h"
#include "aeon/console/console.h"
#include "aeon/resources/shader.h"

namespace aeon
{

shader::shader(resource_manager *creator, const std::string &name, 
    std::uint64_t handle)
:
resource(creator, name, handle),
program_(0),
matrix_handle_(0),
texture0_handle_(0),
color_handle_(0)
{

}

shader::~shader()
{

}

bool shader::__load_impl(stream_ptr stream)
{
    if (!stream->good())
    {
        console::error("[Shader]: Could not load shader: %s", 
            stream->get_name().c_str());
        return false;
    }

    console::debug("[Shader]: Parsing shader file: %s", 
        stream->get_name().c_str());

    //Loop through all lines
    int linenumber = 0;
    int warning_count = 0;
    program_type parsing_program_type = program_type::none;

    while (!stream->eof())
    {
        linenumber++;

        std::string line;
        if (stream->read_line(line) == 0)
            continue;

        if (line == "[vertex]")
        {
            if(
                parsing_program_type == program_type::none || 
                parsing_program_type == program_type::fragment
            )
            {
                // If we had previously read vertex shader source before,
                // we did not expect another [vertex] tag.
                if(!vertex_src_.empty())
                {
                    console::warning("[Shader]: Unexpected line '[vertex]' "
                        "in shader %s at line %u", stream->get_name().c_str(), 
                        linenumber);
                    warning_count++;
                }
                
                parsing_program_type = program_type::vertex;
            }else{
                console::warning("[Shader]: Unexpected line '[vertex]' "
                    "in shader %s at line %u", stream->get_name().c_str(), 
                    linenumber);
                warning_count++;
            }
        }
        else if (line == "[fragment]")
        {
            if (
                parsing_program_type == program_type::none ||
                parsing_program_type == program_type::vertex
                )
            {
                // If we had previously read fragment shader source before,
                // we did not expect another [fragment] tag.
                if(!fragment_src_.empty())
                {
                    console::warning("[Shader]: Unexpected line '[fragment]' "
                        "in shader %s at line %u", stream->get_name().c_str(), 
                        linenumber);
                    warning_count++;
                }
                
                parsing_program_type = program_type::fragment;
            }
            else{
                console::warning("[Shader]: Unexpected line '[fragment]' in "
                    "shader %s at line %u", stream->get_name().c_str(), 
                    linenumber);
                warning_count++;
            }
        }else{
            if(parsing_program_type == program_type::fragment)
            {
                fragment_src_ += line + "\n";
            }
            else if(parsing_program_type == program_type::vertex)
            {
                vertex_src_ += line + "\n";
            }
            else
            {
                console::warning("[Shader]: Unexpected line in shader %s at "
                    "line %u", stream->get_name().c_str(), linenumber);
                warning_count++;
            }
        }
    }

    console::debug("[Shader]: Finished parsing shader file %s with %u "
        "warning(s)", stream->get_name().c_str(), warning_count);

    return true;
}

bool shader::__unload_impl()
{
    return true;
}

bool shader::__finalize_impl()
{
    console::debug("[Shader]: Compiling vertex shader.");
    GLuint vertexshader = __load_shader(vertex_src_, GL_VERTEX_SHADER);

    if (vertexshader == 0)
    {
        console::error("[Shader]: Could not compile vertex shader.");
        return false;
    }

    console::debug("[Shader]: Compiling fragment shader.");
    GLuint fragmentshader = __load_shader(fragment_src_, GL_FRAGMENT_SHADER);

    if (fragmentshader == 0)
    {
        console::error("[Shader]: Could not compile fragment shader.");
        glDeleteShader(fragmentshader);
        return false;
    }

    // Link the shaders together into a program.
    console::debug("[Shader]: Linking program.");
    program_ = __link_program(vertexshader, fragmentshader);

    if (program_ == 0)
    {
        console::error("[Shader]: Error linking program.");
        glDeleteShader(vertexshader);
        glDeleteShader(fragmentshader);
        return false;
    }

    console::debug("[Shader]: Program linked.");

    // Decrease the reference count on our shader objects so they get
    // deleted when the program is deleted.
    glDeleteShader(vertexshader);
    glDeleteShader(fragmentshader);

    // Set up the uniform locations for the matrices in this shader
    matrix_handle_ = glGetUniformLocation(program_, AEON_SHADER_MATRIX_NAME);
    texture0_handle_ = glGetUniformLocation(program_, 
        AEON_SHADER_TEXTURE0_NAME);
    color_handle_ = glGetUniformLocation(program_, AEON_SHADER_COLOR_NAME);

    if(matrix_handle_ == -1)
        console::warning("[Shader]: Could not find '%s' in shader.", 
            AEON_SHADER_MATRIX_NAME);

    if(texture0_handle_ == -1)
        console::warning("[Shader]: Could not find '%s' in shader.",
            AEON_SHADER_TEXTURE0_NAME);

    if (texture0_handle_ == -1)
        console::warning("[Shader]: Could not find '%s' in shader.",
            AEON_SHADER_COLOR_NAME);

    return true;
}

GLuint shader::__load_shader(const std::string &source, GLenum type)
{
    // Create the shader object
    GLuint shader = glCreateShader(type);

    if (shader == 0)
    {
        console::error("[Shader]: Could not create shader OpenGL object.");
        return 0;
    }

    const char *shader_src = source.c_str();

    // Load the shader source
    glShaderSource(shader, 1, &shader_src, NULL);

    // Compile the shader
    glCompileShader(shader);

    // Check the compile status
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    // Did the compile fail?
    if (!status)
    {
        // Do we have a log message? (compile errors etc.?)
        GLint info_len = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);

        if (info_len > 1)
        {
            char *info_log = (char *)malloc(info_len * sizeof(char));
            glGetShaderInfoLog(shader, info_len, NULL, info_log);
            console::error("[Shader]: Error compiling shader: %s", info_log);
            free(info_log);
        }

        // Free the shader resource, since we can't use it anymore.
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint shader::__link_program(GLuint vertexshader, GLuint fragmentshader)
{
    GLuint program = glCreateProgram();

    if (program == 0)
    {
        console::error("[Shader]: Could not create program.");
        return 0;
    }

    // Attach both fragment and vertex shaders to our program.
    glAttachShader(program, vertexshader);
    glAttachShader(program, fragmentshader);

    // Bind attrib locations (the bind points for vertex buffers to the shader)
    glBindAttribLocation(program, AEON_SHADER_ATTRIB_VERTEX_ID, 
        AEON_SHADER_ATTRIB_VERTEX_NAME);
    glBindAttribLocation(program, AEON_SHADER_ATTRIB_TEXCOORD_ID, 
        AEON_SHADER_ATTRIB_TEXCOORD_NAME);

    // Link the program
    glLinkProgram(program);

    // Check the link status
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    // Did linking fail?
    if (!status)
    {
        // Do we have a log message? (linker errors etc.?)
        GLint info_len = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_len);

        if (info_len > 1)
        {
            char *info_log = (char *)malloc(info_len * sizeof(char));
            glGetProgramInfoLog(program, info_len, NULL, info_log);
            console::error("[Shader]: Error linking shader: %s", info_log);
            free(info_log);
        }

        glDeleteProgram(program);
        return 0;
    }

    return program;
}

} /* namespace aeon */
