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

#include <gfx/gfx_shader_manager.h>
#include <resources/wrappers/shader_resource_wrapper.h>

namespace aeon
{
namespace gfx
{

shader_ptr shader_manager::load_shader(resources::shader_ptr shader)
{
    const std::string &path = shader->get_resource_wrapper()->get_path();
    shader_ptr shdr = cache_.get_cached_object(path);

    if (shdr)
        return shdr;

    shdr = __load_shader(shader);

    if (shdr)
        cache_.add_cached_object(path, shdr);

    return shdr;
}

} // namespace gfx
} // namespace aeon
