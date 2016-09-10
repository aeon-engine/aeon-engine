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

#include <gfx/gfx_resource_manager.h>
#include <resources/material.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

class gfx_gles2_device;
class gfx_gles2_material_manager : public gfx::material_manager
{
public:
    explicit gfx_gles2_material_manager(gfx_gles2_device &dev);
    virtual ~gfx_gles2_material_manager() = default;

private:
    gfx::material_ptr __load(resources::material_ptr material) override;

    gfx_gles2_device &device_;
};

} // namespace gles2
} // namespace gfx
} // namespace aeon
