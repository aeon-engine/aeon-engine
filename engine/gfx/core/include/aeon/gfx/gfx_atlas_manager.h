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

#include <aeon/data/atlas.h>
#include <aeon/gfx/gfx_atlas.h>
#include <aeon/gfx/gfx_material.h>
#include <aeon/common/logger.h>

namespace aeon
{
namespace gfx
{

class gfx_atlas_manager
{
public:
    gfx_atlas_manager();
    virtual ~gfx_atlas_manager() = default;

    std::shared_ptr<gfx::atlas> create(const gfx::material_ptr &material, const data::atlas &atlas_data);

private:
    aeon::logger::logger logger_;
};

} // namespace gfx
} // namespace aeon
