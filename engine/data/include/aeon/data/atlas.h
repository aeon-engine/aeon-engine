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
#include <aeon/common/exception.h>

namespace aeon
{
namespace data
{

DEFINE_EXCEPTION_OBJECT(atlas_exception, aeon::common::exception, "Generic Atlas exception.");

/*!
 * Data class representing a texture atlas. A texture atlas is a set of regions (UV coordinates) that represent parts
 * of a texture (usually sprites) on a much larger image. This can be very useful in 2D games with a lot of
 * different sprites, as this doesn't require every sprite to be uploaded to GPU memory seperately.
 */
class atlas
{
public:
    /*!
     * Data class representing a single region (usually a sprite) on a texture atlas.
     * \see atlas
     */
    class region
    {
    public:
        /*!
         * Constructor for a nameless region. These can only be accessed by index.
         * Rectangle coordinates are in UV space.
         */
        region(const float u1_, const float v1_, const float u2_, const float v2_)
            : name()
            , u1(u1_)
            , v1(v1_)
            , u2(u2_)
            , v2(v2_)
        {
        }

        /*!
         * Constructor for a named region. These can be accessed by name or index.
         * Rectangle coordinates are in UV space.
         */
        region(const std::string &name_, const float u1_, const float v1_, const float u2_, const float v2_)
            : name(name_)
            , u1(u1_)
            , v1(v1_)
            , u2(u2_)
            , v2(v2_)
        {
        }

        /*!
         * Destructor
         */
        ~region() = default;

        std::string name;
        float u1, v1;
        float u2, v2;
    };

    /*!
     * Vector of atlas regions.
     */
    using regions = std::vector<region>;

    /*!
     * Constructor for an empty atlas (regions can be added later through push_back).
     */
    atlas() = default;

    /*!
     * Constructor for adding regions up front. This is usually used when loading an atlas.
     * New regions can still be added through push_back.
     */
    explicit atlas(const regions &regions);

    /*!
     * Destructor
     */
    ~atlas() = default;

    /*!
     * Add a new region.
     */
    void push_back(const region &region);

    /*!
     * Get all regions in this atlas.
     */
    const regions &get_regions() const;

    /*!
     * Get a region at a certain index. Will throw an exception if this region can not be found.
     */
    const region &at(const int index) const;

    /*!
     * Get a region by name. Will throw an exception if this region can not be found.
     */
    const region &at(const std::string &name) const;

    /*!
     * Get the amount of regions in this atlas.
     */
    std::size_t size() const;

private:
    regions regions_;
};

} // namespace data
} // namespace aeon
