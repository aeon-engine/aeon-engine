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

#include <typeinfo>
#include <glm/vec2.hpp>
#include <iostream>

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
        : left_()
        , top_()
        , right_()
        , bottom_()
    {
    }

    /*!
     * Constructor
     */
    rectangle(const T left, const T top, const T right, const T bottom)
        : left_(left)
        , top_(top)
        , right_(right)
        , bottom_(bottom)
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
        : left_(static_cast<T>(other.left()))
        , top_(static_cast<T>(other.top()))
        , right_(static_cast<T>(other.right()))
        , bottom_(static_cast<T>(other.bottom()))
    {
    }

    /*!
     * Check if this rectangle is empty or in other words; if it has no width
     * or height.
     * \return True when this rectangle has a width or height of 0.
     */
    auto is_empty() const
    {
        return width() == T() || height() == T();
    }

    /*!
     * Get the size (width and height) of this rectangle as a Size2D. Values may
     * be negative.
     * \return The size of the rectangle as Size2D.
     */
    template <typename U>
    auto size() const
    {
        return glm::vec2(width(), height());
    }

    auto left() const
    {
        return left_;
    }

    auto top() const
    {
        return top_;
    }

    auto right() const
    {
        return right_;
    }

    auto bottom() const
    {
        return bottom_;
    }

    auto width() const
    {
        return right_ - left_;
    }

    auto height() const
    {
        return bottom_ - top_;
    }

private:
    T left_;
    T top_;
    T right_;
    T bottom_;
};

/*!
 * Equals operator overload for rectangle.
 */
template <typename T>
inline bool operator==(const rectangle<T> &lhs, const rectangle<T> &rhs)
{
    return lhs.left() == rhs.left() && lhs.top() == rhs.top() && lhs.right() == rhs.right() &&
           lhs.bottom() == rhs.bottom();
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
    return os << "rectangle<" << typeid(T).name() << ">(" << rect.left() << "," << rect.top() << "," << rect.right()
              << "," << rect.bottom() << ")";
}

} // namespace types
} // namespace common
} // namespace aeon
