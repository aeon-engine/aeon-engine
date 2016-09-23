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

#include <vector>
#include <string>
#include <glm/vec2.hpp>
#include <common/exception.h>

namespace aeon
{
namespace data
{

DEFINE_EXCEPTION_OBJECT(atlas_exception, aeon::common::exception, "Generic Atlas exception.");

class atlas
{
public:
    class region
    {
    public:
        region(float u1_, float v1_, float u2_, float v2_, glm::vec2 size_)
            : name()
            , u1(u1_)
            , v1(v1_)
            , u2(u2_)
            , v2(v2_)
            , size(size_)
        {
        }

        region(const std::string &name_, float u1_, float v1_, float u2_, float v2_, glm::vec2 size_)
            : name(name_)
            , u1(u1_)
            , v1(v1_)
            , u2(u2_)
            , v2(v2_)
            , size(size_)
        {
        }

        ~region() = default;

        std::string name;
        float u1, v1;
        float u2, v2;
        glm::vec2 size;
    };

    using regions = std::vector<region>;

    atlas() = default;
    explicit atlas(const regions &regions);

    ~atlas() = default;

    void push_back(const region &region);

    const regions &get_regions() const;

    const region &at(const int index) const;
    const region &at(const std::string &name) const;

    std::size_t size() const;

private:
    regions regions_;
};

} // namespace data
} // namespace aeon
