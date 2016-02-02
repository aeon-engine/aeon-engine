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

#include <common/object_cache.h>
#include <resources/wrappers/material_resource_wrapper.h>
#include <resources/material.h>
#include <gfx/gfx_material.h>

namespace aeon
{
namespace gfx
{

class material_manager
{
public:
    material_manager() = default;
    virtual ~material_manager() = default;

    material_ptr load_material(resources::material_ptr material);

private:
    virtual material_ptr __load_material(resources::material_ptr material) = 0;

    common::object_cache<gfx::material> cache_;
};

} // namespace gfx
} // namespace aeon
