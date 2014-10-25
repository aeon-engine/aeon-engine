#ifndef material_h__
#define material_h__

namespace aeon
{

class material : public resource
{
public:
    material(resource_manager *creator, const std::string &name,
             std::uint64_t handle);
    virtual ~material();

    glm::fvec4 ambient;
    glm::fvec4 diffuse;
    glm::fvec4 specular;
    glm::fvec4 emission;
    float shininess;
    shader_ptr shader_resource;
    std::array<texture_ptr, AEON_MATERIAL_MAX_TEXTURE_BINDS> texture_resource;

protected:
    virtual bool __load_impl(stream_ptr stream);
    virtual bool __unload_impl();
    virtual bool __finalize_impl();

    void __read_attributes(configfile &material_file);
    void __read_and_load_shader(configfile &material_file);
    void __read_and_load_textures(configfile &material_file);
};

typedef std::shared_ptr<material> material_ptr;

} /* namespace aeon */

#endif /* material_h__ */
