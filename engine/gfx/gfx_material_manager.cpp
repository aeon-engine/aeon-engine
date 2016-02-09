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

#include <gfx/gfx_material_manager.h>
#include <resources/wrappers/material_resource_wrapper.h>

namespace aeon
{
namespace gfx
{

material_ptr material_manager::load_material(resources::material_ptr material)
{
    const std::string &path = material->get_resource_wrapper()->get_path();
    material_ptr mat = cache_.get_cached_object(path);

    if (mat)
        return mat;

    mat = __load_material(material);

    if (mat)
        cache_.add_cached_object(path, mat);

    return mat;
}

} // namespace gfx
} // namespace aeon
