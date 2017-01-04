/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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
        explicit region(const float u1, const float v1, const float u2, const float v2, const float width,
                        const float height)
            : name()
            , u1(u1)
            , v1(v1)
            , u2(u2)
            , v2(v2)
            , width(width)
            , height(height)
        {
        }

        /*!
         * Constructor for a named region. These can be accessed by name or index.
         * Rectangle coordinates are in UV space.
         */
        explicit region(const std::string &name, const float u1, const float v1, const float u2, const float v2,
                        const float width, const float height)
            : name(name)
            , u1(u1)
            , v1(v1)
            , u2(u2)
            , v2(v2)
            , width(width)
            , height(height)
        {
        }

        /*!
         * Destructor
         */
        ~region() = default;

        /*!
         * Get the size of the atlas region in pixels.
         * If the atlas was loaded from file, it will return 0, 0.
         */
        auto get_size() const
        {
            return glm::vec2{width, height};
        }

        std::string name;
        float u1, v1;
        float u2, v2;
        float width, height;
    };

    /*!
     * Constructor for an empty atlas (regions can be added later through push_back).
     */
    atlas() = default;

    /*!
     * Constructor for adding regions up front. This is usually used when loading an atlas.
     * New regions can still be added through push_back.
     */
    explicit atlas(const std::vector<region> &regions);

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
    auto get_regions() const -> const std::vector<region> &;

    /*!
     * Get a region at a certain index. Will throw an exception if this region can not be found.
     */
    auto at(const unsigned int index) const -> const region &;

    /*!
     * Get a region by name. Will throw an exception if this region can not be found.
     */
    auto at(const std::string &name) const -> const region &;

    /*!
     * Get the amount of regions in this atlas.
     */
    auto size() const -> std::size_t;

private:
    std::vector<region> regions_;
};

} // namespace data
} // namespace aeon
