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

#include <aeon/gfx/gfx_material_manager.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

class gfx_gl_material_manager : public gfx::material_manager
{
public:
    explicit gfx_gl_material_manager() = default;
    virtual ~gfx_gl_material_manager() = default;

private:
    std::shared_ptr<material> create(const std::shared_ptr<shader> &shader,
                                     const material::sampler_map &samplers) override;
};

} // namespace gl
} // namespace gfx
} // namespace aeon
