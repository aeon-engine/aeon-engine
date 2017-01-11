/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#include <aeon/gfx/gfx_material.h>
#include <aeon/gfx/gfx_shader.h>
#include <aeon/gfx/gfx_texture.h>

#include <memory>
#include <string>

namespace aeon
{
namespace gfx
{

class material_manager
{
public:
    material_manager() = default;
    virtual ~material_manager() = default;

    virtual std::shared_ptr<material> create(const std::shared_ptr<shader> &shader,
                                             const std::map<std::string, std::shared_ptr<texture>> &samplers) = 0;
};

} // namespace gfx
} // namespace aeon
