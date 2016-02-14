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
#include <map>
#include <vector>
#include <string>
#include <memory>

namespace aeon
{
namespace resources
{

class atlas_region
{
public:
    explicit atlas_region(float u1_, float v1_, float u2_, float v2_)
        : u1(u1_)
        , v1(v1_)
        , u2(u2_)
        , v2(v2_)
    {
    }

    ~atlas_region() = default;

    float u1, v1;
    float u2, v2;
};

using atlas_regions = std::vector<atlas_region>;
using atlas_region_names = std::map<std::string, int>;

class atlas : public resource
{
public:
    explicit atlas(resource_wrapper_ptr wrapper, material_ptr material, const atlas_regions &regions,
        const atlas_region_names &names);

    virtual ~atlas() = default;

    atlas_region get_region_by_index(int index);
    atlas_region get_region_by_name(const std::string &name);

    atlas_resource_wrapper_ptr get_atlas_resource_wrapper()
    {
        return std::dynamic_pointer_cast<atlas_resource_wrapper>(get_resource_wrapper());
    }

private:
    atlas_regions regions_;
    atlas_region_names names_;
};

using atlas_ptr = std::shared_ptr<atlas>;

} // namespace resources
} // namespace aeon
