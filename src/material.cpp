/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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
    texture_resource({{nullptr}})
{
}

material::~material()
{
}

bool material::__load_impl(aeon::streams::stream_ptr stream)
{
    // A material file has the same syntax as a config file
    aeon::utility::configfile material_file;

    material_file.load(std::dynamic_pointer_cast<aeon::streams::file_stream>(stream));

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

void material::__read_attributes(aeon::utility::configfile &material_file)
{
    std::string ambient_str = material_file.get_string(
        "ambient",
        string_utils::vector4f_to_string(glm::fvec4(AEON_MATERIAL_DEFAULT_AMBIENT))
    );
    ambient = string_utils::string_to_vector4f(ambient_str);

    std::string diffuse_str = material_file.get_string(
        "diffuse",
        string_utils::vector4f_to_string(glm::fvec4(AEON_MATERIAL_DEFAULT_DIFFUSE))
    );
    diffuse = string_utils::string_to_vector4f(diffuse_str);

    std::string specular_str = material_file.get_string(
        "specular",
        string_utils::vector4f_to_string(glm::fvec4(AEON_MATERIAL_DEFAULT_SPECULAR))
    );
    specular = string_utils::string_to_vector4f(specular_str);

    std::string emission_str = material_file.get_string(
        "emission",
        string_utils::vector4f_to_string(glm::fvec4(AEON_MATERIAL_DEFAULT_EMISSION))
    );
    emission = string_utils::string_to_vector4f(emission_str);

    shininess = material_file.get_float(
        "shininess", AEON_MATERIAL_DEFAULT_SHININESS);
}

void material::__read_and_load_shader(aeon::utility::configfile &material_file)
{
    // Read the path of the texture
    std::string shader_filename =
        material_file.get_string("shader", "");

    // Don't read empty shader paths
    if (shader_filename.empty())
        return;

    shader_resource =
        shader_manager::get_singleton().load(shader_filename);
}

void material::__read_and_load_textures(aeon::utility::configfile &material_file)
{
    size_t texture_count = texture_resource.size();
    for (size_t i = 0; i < texture_count; ++i)
    {
        std::string texture_key = "texture" + std::to_string(i);

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

} // namespace aeon
