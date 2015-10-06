/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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
#include <string>
#include <vector>
#include <memory>

namespace aeon
{
namespace platform
{

class video_mode
{
public:
    video_mode(int w, int h, int r, int g, int b, int rr) :
        width(w),
        height(h),
        red_bits(r),
        green_bits(g),
        blue_bits(b),
        refresh_rate(rr)
    {
    }

    int width;
    int height;
    int red_bits;
    int green_bits;
    int blue_bits;
    int refresh_rate;
};

using video_modes = std::vector<video_mode>;

class gamma_ramp_data
{
public:
    gamma_ramp_data(int r, int g, int b) :
        red(r),
        green(g),
        blue(b)
    {
    }

    int red;
    int green;
    int blue;
};

using gamma_ramp = std::vector<gamma_ramp_data>;

class platform_monitor
{
public:
    platform_monitor(int width, int height, int x, int y, bool primary) :
        physical_width_(width),
        physical_height_(height),
        x_(x),
        y_(y),
        primary_(primary)
    {
    }

    virtual ~platform_monitor() = default;

    virtual void set_gramma(float gamma) = 0;

    virtual gamma_ramp get_gamma_ramp() = 0;
    virtual void set_gamma_ramp(gamma_ramp ramp) = 0;

    virtual video_mode get_video_mode() = 0;
    virtual video_modes get_video_modes() = 0;

    /*!
     * Get the physical size of the display in millimeters. This size can come from
     * EDID data, or may be calculated based on DPI. This size is not guaranteerd to
     * be accurate. On certain platforms this may always be 0.
     */
    void get_physical_dimensions(int &width, int &height) const
    {
        width = physical_width_;
        height = physical_height_;
    }

    /*!
     * Returns the position, in screen coordinates, of the upper-left corner of the
     * monitor. On certain platforms this may always be 0.
     */
    void get_position(int &x, int &y) const
    {
        x = x_;
        y = y_;
    }

    /*!
     * Returns true of this is the primary monitor.
     */
    bool is_primary() const
    {
        return primary_;
    }

    /*!
     * Returns the name of the monitor, which usually consists of the make and model.
     * Monitor names are not guaranteed to be unique, or they may not even be available
     * at all on some platforms. Do not use for anything other than usability purposes
     * (like configuration screens for the end-user).
     */
    const std::string &get_name() const
    {
        return name_;
    }

private:
    int physical_width_;
    int physical_height_;
    int x_;
    int y_;
    bool primary_;
    std::string name_;
};

using platform_monitor_ptr = std::unique_ptr<platform_monitor>;
using platform_monitors = std::vector<platform_monitor_ptr>;

} // namespace platform
} // namespace aeon
