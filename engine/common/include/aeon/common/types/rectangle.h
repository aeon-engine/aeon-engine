/*
 * Copyright (c) 2012-2017 Robin Degen
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
inline auto operator==(const rectangle<T> &lhs, const rectangle<T> &rhs)
{
    return lhs.left() == rhs.left() && lhs.top() == rhs.top() && lhs.right() == rhs.right() &&
           lhs.bottom() == rhs.bottom();
}

/*!
 * Not-Equals operator overload for rectangle.
 */
template <typename T>
inline auto operator!=(const rectangle<T> &lhs, const rectangle<T> &rhs)
{
    return !(lhs == rhs);
}

/*!
 * Stream operator overload for rectangle. This allows rectangle to be used with std streams
 * like std::cout and std::stringstream.
 */
template <typename T>
inline auto &operator<<(std::ostream &os, const rectangle<T> &rect)
{
    return os << "rectangle<" << typeid(T).name() << ">(" << rect.left() << "," << rect.top() << "," << rect.right()
              << "," << rect.bottom() << ")";
}

} // namespace types
} // namespace common
} // namespace aeon
