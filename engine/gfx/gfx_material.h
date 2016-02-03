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

#include <gfx/gfx_shader.h>
#include <gfx/gfx_texture.h>

namespace aeon
{
namespace gfx
{

class material : public common::cached_object
{
public:
    material();
    virtual ~material();

    virtual void bind() = 0;

    shader_ptr get_shader() const;
    texture_ptr get_texture() const;

protected:
    shader_ptr shader_;
    texture_ptr texture_;
};

using material_ptr = std::shared_ptr<material>;

} // namespace gfx
} // namespace aeon
