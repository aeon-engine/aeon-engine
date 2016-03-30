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

#include <resources/resource.h>
#include <resources/exceptions.h>
#include <resources/material.h>
#include <resources/wrappers/atlas_resource_wrapper.h>
#include <common/buffer.h>
#include <common/logger.h>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <glm/vec2.hpp>

namespace aeon
{
namespace resources
{

class atlas_region
{
public:
    explicit atlas_region(float u1_, float v1_, float u2_, float v2_, glm::vec2 size_)
        : u1(u1_)
        , v1(v1_)
        , u2(u2_)
        , v2(v2_)
        , size(size_)
    {
    }

    ~atlas_region() = default;

    float u1, v1;
    float u2, v2;
    glm::vec2 size;
};

using atlas_regions = std::vector<atlas_region>;
using atlas_region_names = std::map<std::string, int>;

class atlas : public resource
{
public:
    /*!
     * Constructor used by the atlas codec to load an atlas
     */
    explicit atlas(resource_wrapper_ptr wrapper, resources::material_ptr material, const atlas_regions &regions,
                   const atlas_region_names &names);

    virtual ~atlas();

    resources::material_ptr get_material() const;

    resources::atlas_regions get_regions() const;
    resources::atlas_region_names get_region_names() const;

    atlas_resource_wrapper_ptr get_atlas_resource_wrapper() const
    {
        return std::dynamic_pointer_cast<atlas_resource_wrapper>(get_resource_wrapper());
    }

private:
    aeon::logger::logger logger_;

    resources::atlas_regions regions_;
    resources::atlas_region_names names_;

    resources::material_ptr material_;
};

using atlas_ptr = std::shared_ptr<atlas>;

} // namespace resources
} // namespace aeon
