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
#include <resources/shader.h>
#include <gfx/gfx_shader.h>

namespace aeon
{
namespace gfx
{

class shader_manager
{
public:
    shader_manager() = default;
    virtual ~shader_manager() = default;

    shader_ptr load_shader(resources::shader_ptr shader);

private:
    virtual shader_ptr __load_shader(resources::shader_ptr shader) = 0;

    common::object_cache<gfx::shader> cache_;
};

} // namespace gfx
} // namespace aeon
