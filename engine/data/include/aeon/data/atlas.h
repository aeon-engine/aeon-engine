/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <vector>
#include <string>
#include <aeon/math/vector2.h>
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

        region(const region &) = default;
        auto operator=(const region &) -> region & = default;

        region(region &&) noexcept = default;
        auto operator=(region &&) noexcept -> region & = default;

        /*!
         * Get the size of the atlas region in pixels.
         * If the atlas was loaded from file, it will return 0, 0.
         */
        auto get_size() const
        {
            return math::vector2<float>{width, height};
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

    atlas(const atlas &) = default;
    auto operator=(const atlas &) -> atlas & = default;

    atlas(atlas &&) noexcept = default;
    auto operator=(atlas &&) noexcept -> atlas & = default;

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
