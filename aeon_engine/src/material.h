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
    virtual bool __load_impl(aeon::streams::stream_ptr stream);
    virtual bool __unload_impl();
    virtual bool __finalize_impl();

    void __read_attributes(aeon::utility::configfile &material_file);
    void __read_and_load_shader(aeon::utility::configfile &material_file);
    void __read_and_load_textures(aeon::utility::configfile &material_file);
};

typedef std::shared_ptr<material> material_ptr;

} // namespace aeon

#endif // material_h__
