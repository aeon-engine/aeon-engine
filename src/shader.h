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

protected:
    enum class program_type
    {
        none,
        fragment,
        vertex
    };

    virtual bool __load_impl(stream_ptr stream);
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
#define aeon_empty_shader shader_ptr()

} /* namespace aeon */

#endif /* shader_h__ */
