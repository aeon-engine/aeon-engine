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

gfx_atlas_manager::gfx_atlas_manager()
    : logger_(common::logger::get_singleton(), "Gfx::AtlasManager")
{
}

atlas_ptr gfx_atlas_manager::create(const gfx::material_ptr &material, const data::atlas &atlas_data)
{
    return std::make_shared<gfx::atlas>(material, atlas_data);
}

} // namespace gfx
} // namespace aeon
