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

#include <common/cached_object.h>
#include <common/exception.h>
#include <resources/atlas.h>
#include <gfx/gfx_material.h>
#include <memory>

namespace aeon
{
namespace gfx
{

DEFINE_EXCEPTION_OBJECT(atlas_exception, aeon::common::exception, "Generic Atlas exception.");

class atlas : public common::cached_object
{
    friend class gfx_atlas_manager;

public:
    atlas();
    explicit atlas(gfx::material_ptr material, glm::vec2 sprite_size);
    virtual ~atlas() = default;

    resources::atlas_region get_region_by_index(int index);
    resources::atlas_region get_region_by_name(const std::string &name);

    gfx::material_ptr get_material() const;

private:
    void __calculate_atlas_regions(glm::vec2 sprite_size);

    aeon::logger::logger logger_;

    resources::atlas_regions regions_;
    resources::atlas_region_names names_;

    gfx::material_ptr material_;
};

using atlas_ptr = std::shared_ptr<atlas>;

} // namespace gfx
} // namespace aeon
