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
        : x()
        , y()
        , width()
        , height()
    {
    }

    /*!
     * Constructor
     */
    rectangle(T x_, T y_, T width_, T height_)
        : x(x_)
        , y(y_)
        , width(width_)
        , height(height_)
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
        : x(static_cast<T>(other.x))
        , y(static_cast<T>(other.y))
        , width(static_cast<T>(other.width))
        , height(static_cast<T>(other.height))
    {
    }

    /*!
     * Check if this rectangle is empty or in other words; if it has no width
     * or height.
     * \return True when this rectangle has a width or height of 0.
     */
    bool is_empty() const
    {
        return width == T() || height == T();
    }

    /*!
     * Get the size (width and height) of this rectangle as a Size2D. Values may
     * be negative.
     * \return The size of the rectangle as Size2D.
     */
    template <typename U>
    glm::vec2 size() const
    {
        return glm::vec2(width, height);
    }

    T x;
    T y;
    T width;
    T height;
};

/*!
 * Equals operator overload for rectangle.
 */
template <typename T>
inline bool operator==(const rectangle<T> &lhs, const rectangle<T> &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.width == rhs.width && lhs.height == rhs.height;
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
    return os << "rectangle<" << typeid(T).name() << ">(" << rect.x << "," << rect.y << "," << rect.width << ","
              << rect.height << ")";
}

} // namespace types
} // namespace common
} // namespace aeon
