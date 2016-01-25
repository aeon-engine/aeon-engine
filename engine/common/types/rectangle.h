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

#include <typeinfo>
#include <glm/vec2.hpp>
#include <iostream>
#include <cmath>

namespace aeon
{
namespace common
{
namespace types
{

/*!
 * rectangle class. A rectangle has a left, top, right and bottom value.
 */
template <typename T>
class rectangle
{
public:
    /*!
     * Constructor
     * The begin and end template types are default constructed
     */
    rectangle()
        : left()
        , top()
        , right()
        , bottom()
    {
    }

    /*!
     * Constructor
     * \param left Left offset of the rectangle
     * \param top Top offset of the rectangle
     * \param right Right offset of the rectangle
     * \param bottom Bottom offset of the rectangle
     */
    rectangle(T left_, T top_, T right_, T bottom_)
        : left(left_)
        , top(top_)
        , right(right_)
        , bottom(bottom_)
    {
    }

    /*!
     * Constructor
     * Converts a rectangle class from one type to another (for example from int to double)
     * Note: Given template types must be convertible to each other through static_cast.
     * \param other A rectangle class of another template type
     */
    template <typename U>
    explicit rectangle(const rectangle<U> &other)
        : left(static_cast<T>(other.left))
        , top(static_cast<T>(other.top))
        , right(static_cast<T>(other.right))
        , bottom(static_cast<T>(other.bottom))
    {
    }

    /*!
     * Check if this rectangle is empty or in other words; if it has no width
     * or height.
     * \return True when this rectangle has a width or height of 0.
     */
    bool is_empty() const
    {
        return right == left || bottom == top;
    }

    /*!
     * Get the width of this rectangle. The width may be negative.
     * \return The width of this rectangle (right - left)
     */
    template <typename U>
    U width() const
    {
        return static_cast<U>(right - left);
    }

    /*!
     * Get the height of this rectangle. The height may be negative.
     * \return The height of this rectangle (bottom - top)
     */
    template <typename U>
    U height() const
    {
        return static_cast<U>(bottom - top);
    }

    /*!
     * Get the size (width and height) of this rectangle as a Size2D. Values may
     * be negative.
     * \return The size of the rectangle as Size2D.
     */
    template <typename U>
    glm::vec2 size()
    {
        return glm::vec2(width<float>(), height<float>());
    }

    /*!
     * Set a rectangle's position through a Vector2.
     * \param rect A rectangle
     * \param p A Vector2 containing a position.
     * \return A new rectangle positioned on the given position.
     */
    static rectangle<T> move_to(const rectangle<T> &rect, const glm::vec2 &p)
    {
        return rectangle<T>(p.x, p.y, (rect.width<T>()) + static_cast<T>(p.x),
                            (rect.height<T>()) + static_cast<T>(p.y));
    }

    /*!
     * Check if Vector2 point is within a rectangle
     * \param outer A rectangle
     * \param inner A Vector2 containing a position.
     * \return True of the given Vector2 value is within the rectangle.
     */
    static bool contains(const rectangle<T> &outer, const glm::vec2 &inner)
    {
        return outer.left <= static_cast<T>(inner.x) && static_cast<T>(inner.x) < outer.right &&
               outer.top <= static_cast<T>(inner.y) && static_cast<T>(inner.y) < outer.bottom;
    }

    /*!
     * Check if a rectangle is within another rectangle. The entire inner rectangle
     * must be contained within the outer for this function to return true. Use the
     * Overlaps function if you only require intersection detection.
     * \param outer A rectangle
     * \param inner A rectangle
     * \return True of the given inner rectangle is fully contained within the outer rectangle.
     */
    static bool contains(const rectangle<T> &outer, const rectangle<T> &inner)
    {
        return outer.left <= inner.left && inner.right <= outer.right && outer.top <= inner.top &&
               inner.bottom <= outer.bottom;
    }

    /*!
     * Check if a rectangle intersects another rectangle.
     * \param outer A rectangle
     * \param inner A rectangle
     * \return True of the given inner rectangle is intersecting the outer rectangle.
     */
    static bool Overlaps(const rectangle<T> &r1, const rectangle<T> &r2)
    {
        return r1.left < r2.right && r2.left < r1.right && r1.top < r2.bottom && r2.top < r1.bottom;
    }

    /*!
     * Get the intersection rectangle of 2 overlapping rectangles. See graphic below:
     *
     *   +===============+
     *   |      r1       |
     *   |      +========|====+
     *   |      | result |    |
     *   +======|========+    |
     *          |     r2      |
     *          +=============+
     *
     * \param r1 A rectangle
     * \param r2 A rectangle
     * \return An intersection of the 2 given rectangles.
     */
    static rectangle<T> intersection(const rectangle<T> &r1, const rectangle<T> &r2)
    {
        return rectangle<T>(std::max<T>(r1.left, r2.left), std::max<T>(r1.top, r2.top), std::min<T>(r1.right, r2.right),
                            std::min<T>(r1.bottom, r2.bottom));
    }

    T left;
    T top;
    T right;
    T bottom;
};

/*!
 * Equals operator overload for rectangle.
 */
template <typename T>
inline bool operator==(const rectangle<T> &lhs, const rectangle<T> &rhs)
{
    return lhs.left == rhs.left && lhs.top == rhs.top && lhs.right == rhs.right && lhs.bottom == rhs.bottom;
}

/*!
 * Not-Equals operator overload for rectangle.
 */
template <typename T>
inline bool operator!=(const rectangle<T> &lhs, const rectangle<T> &rhs)
{
    return !(lhs == rhs);
}

/*!
 * Stream operator overload for rectangle. This allows rectangle to be used with std streams
 * like std::cout and std::stringstream.
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &os, const rectangle<T> &rect)
{
    return os << "rectangle<" << typeid(T).name() << ">(" << rect.left << "," << rect.top << "," << rect.right << ","
              << rect.bottom << ")";
}

} // namespace types
} // namespace common
} // namespace aeon
