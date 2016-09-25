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

#include <resources/image.h>
#include <gfx/gfx_texture.h>

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
    resource_manager() = default;
    virtual ~resource_manager() = default;

    virtual std::shared_ptr<gfx_type> create(const resource_type &res) = 0;
};

using texture_manager = resource_manager<gfx::texture, resources::image>;

} // namespace gfx
} // namespace aeon
