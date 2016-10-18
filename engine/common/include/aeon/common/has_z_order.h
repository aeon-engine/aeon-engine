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

namespace aeon
{
namespace common
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
    int get_zorder() const
    {
        return zorder_;
    }

private:
    int zorder_;
};

} // namespace common
} // namespace aeon
