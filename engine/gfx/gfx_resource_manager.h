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

#pragma once

#include <resources/shader.h>
#include <gfx/gfx_shader.h>

#include <resources/image.h>
#include <gfx/gfx_texture.h>

#include <resources/material.h>
#include <gfx/gfx_material.h>

#include <common/object_cache.h>
#include <memory>
#include <string>

namespace aeon
{
namespace gfx
{

template <typename gfx_type, typename resource_type>
class resource_manager
{
public:
    using gfx_type_ptr = std::shared_ptr<gfx_type>;
    using resource_type_ptr = std::shared_ptr<resource_type>;

    resource_manager() = default;
    virtual ~resource_manager() = default;

    gfx_type_ptr load(resource_type_ptr res)
    {
        const std::string &path = res->get_resource_wrapper()->get_path();
        gfx_type_ptr gfx_res = cache_.get_cached_object(path);

        if (gfx_res)
            return gfx_res;

        gfx_res = __load(res);

        if (gfx_res)
            cache_.add_cached_object(path, gfx_res);

        return gfx_res;
    }

private:
    virtual gfx_type_ptr __load(resource_type_ptr material) = 0;

    common::object_cache<gfx_type> cache_;
};

using shader_manager = resource_manager<gfx::shader, resources::shader>;
using texture_manager = resource_manager<gfx::texture, resources::image>;
using material_manager = resource_manager<gfx::material, resources::material>;

} // namespace gfx
} // namespace aeon
