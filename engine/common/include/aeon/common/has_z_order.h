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

class has_z_order
{
public:
    has_z_order()
        : zorder_(0)
    {
    }

    explicit has_z_order(int zorder)
        : zorder_(zorder)
    {
    }

    virtual ~has_z_order() = default;

    void set_zorder(int zorder)
    {
        zorder_ = zorder;
    }

    int get_zorder() const
    {
        return zorder_;
    }

private:
    int zorder_;
};

} // namespace common
} // namespace aeon
