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
#include <resources/image.h>
#include <common/logger.h>

namespace aeon
{
namespace gfx
{
namespace null
{

class gfx_null_texture_manager : public gfx::texture_manager
{
public:
    gfx_null_texture_manager();
    virtual ~gfx_null_texture_manager() = default;

private:
    texture_ptr __load(resources::image_ptr image) override;

    aeon::logger::logger logger_;
};

} // namespace null
} // namespace gfx
} // namespace aeon
