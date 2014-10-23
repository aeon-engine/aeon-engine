#include "stdafx.h"

namespace aeon
{

material::material(resource_manager *creator, const std::string &name,
    std::uint64_t handle) :
    resource(creator, name, handle),
    ambient(AEON_MATERIAL_DEFAULT_AMBIENT),
    diffuse(AEON_MATERIAL_DEFAULT_DIFFUSE),
    specular(AEON_MATERIAL_DEFAULT_SPECULAR),
    emission(AEON_MATERIAL_DEFAULT_EMISSION),
    shininess(AEON_MATERIAL_DEFAULT_SHININESS),
    shader_resource(nullptr),
    texture_resource({nullptr})
{

}

material::~material()
{

}

bool material::__load_impl(stream_ptr stream)
{
    // A material file has the same syntax as a config file
    configfile material_file;
    
    if (!material_file.load(stream))
        return false;

    // Read all the material settings
    __read_attributes(material_file);

    // Read and load the shader (if any)
    __read_and_load_shader(material_file);

    // Read and load all possible texture binds
    __read_and_load_textures(material_file);

    return true;
}

bool material::__unload_impl()
{
    // Remove all references to the textures. This should be done automatically 
    // on the stack, but this is more predictable.
    size_t texture_count = texture_resource.size();
    for (size_t i = 0; i < texture_count; ++i)
    {
        if (texture_resource[i])
            texture_manager::get_singleton().unload(texture_resource[i]);

        texture_resource[i] = nullptr;
    }

    return true;
}

bool material::__finalize_impl()
{
    // Do stuff on gpu thread
    return true;
}

void material::__read_attributes(configfile &material_file)
{
    ambient = material_file.get_vector4f(
        "material.ambient", glm::fvec4(AEON_MATERIAL_DEFAULT_AMBIENT));
    diffuse = material_file.get_vector4f(
        "material.diffuse", glm::fvec4(AEON_MATERIAL_DEFAULT_DIFFUSE));
    specular = material_file.get_vector4f(
        "material.specular", glm::fvec4(AEON_MATERIAL_DEFAULT_SPECULAR));
    emission = material_file.get_vector4f(
        "material.emission", glm::fvec4(AEON_MATERIAL_DEFAULT_EMISSION));
    shininess = material_file.get_float(
        "material.shininess", AEON_MATERIAL_DEFAULT_SHININESS);
}

void material::__read_and_load_shader(configfile &material_file)
{
    // Read the path of the texture
    std::string shader_filename =
        material_file.get_string("material.shader", "");

    // Don't read empty shader paths
    if (shader_filename.empty())
        return;

    shader_resource =
        shader_manager::get_singleton().load(shader_filename);
}

void material::__read_and_load_textures(configfile &material_file)
{
    size_t texture_count = texture_resource.size();
    for (size_t i = 0; i < texture_count; ++i)
    {
        std::string texture_key = "material.texture" + std::to_string(i);

        // Check if this texture is defined in the material
        if (!material_file.has_entry(texture_key))
            continue;

        // Read the path of the texture
        std::string texture_filename =
            material_file.get_string(texture_key, "");

        // Don't read empty texture paths
        if (texture_filename.empty())
            continue;

        // Load the texture
        texture_resource[i] = 
            texture_manager::get_singleton().load(texture_filename);
    }
}

} /* namespace aeon */
