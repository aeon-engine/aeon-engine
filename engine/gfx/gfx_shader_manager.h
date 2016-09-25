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

#include <aeon/data/shader.h>
#include <gfx/gfx_shader.h>

#include <memory>

namespace aeon
{
namespace gfx
{

class shader_manager
{
public:
    shader_manager() = default;
    virtual ~shader_manager() = default;

    virtual std::shared_ptr<shader> create(const data::shader &shader_data) = 0;
};

} // namespace gfx
} // namespace aeon
