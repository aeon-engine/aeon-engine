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

namespace aeon::common
{

/*!
 * Base class for objects that have a z-order. These
 * objects are usually sorted by z-order for a painter's
 * algorithm.
 */
class has_z_order
{
public:
    /*!
     * Constructor, default z-order is 0.
     */
    has_z_order()
        : zorder_(0)
    {
    }

    /*!
     * Constructor
     */
    explicit has_z_order(const int zorder)
        : zorder_(zorder)
    {
    }

    /*!
     * Destructor
     */
    virtual ~has_z_order() = default;

    /*!
     * Set the z-order for this object.
     */
    void set_zorder(const int zorder)
    {
        zorder_ = zorder;
    }

    /*!
     * Get the z-order for this object.
     */
    auto get_zorder() const
    {
        return zorder_;
    }

private:
    int zorder_;
};

} // namespace aeon::common
