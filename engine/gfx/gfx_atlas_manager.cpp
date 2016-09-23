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

#include <gfx/gfx_atlas_manager.h>
#include <gfx/gfx_device.h>

namespace aeon
{
namespace gfx
{

gfx_atlas_manager::gfx_atlas_manager(device &dev)
    : logger_(common::logger::get_singleton(), "Gfx::AtlasManager")
    , device_(dev)
{
}

atlas_ptr gfx_atlas_manager::__load(resources::atlas_ptr atlas_resource)
{
    material_manager &material_manager = device_.get_material_manager();
    atlas_ptr atlas = std::make_shared<gfx::atlas>();
    atlas->material_ = material_manager.load(atlas_resource->get_material());
    atlas->atlas_ = atlas_resource->get_data();
    return atlas;
}

} // namespace gfx
} // namespace aeon
