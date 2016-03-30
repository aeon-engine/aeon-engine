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
#include <resources/atlas.h>
#include <gfx/gfx_atlas.h>
#include <common/logger.h>

namespace aeon
{
namespace gfx
{

class device;
class gfx_atlas_manager : public gfx::resource_manager<gfx::atlas, resources::atlas>
{
public:
    gfx_atlas_manager(device &dev);
    virtual ~gfx_atlas_manager() = default;

private:
    atlas_ptr __load(resources::atlas_ptr atlas_resource) override;

    aeon::logger::logger logger_;
    device &device_;
};

} // namespace gfx
} // namespace aeon
