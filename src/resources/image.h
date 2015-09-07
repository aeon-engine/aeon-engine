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

#include <common/buffer.h>
#include <aeon/streams.h>
#include <vector>
#include <memory>

namespace aeon
{
namespace resources
{

class image
{
public:
    enum class pixel_format
    {
        rgb,
        rgba,
    };

    image();
    ~image();

    void set_data(common::buffer_ptr_u8 buffer, unsigned int width,
                  unsigned int height,
                  pixel_format pixelformat = pixel_format::rgba);

    common::buffer_ptr_u8 get_data() { return buffer_; }
    unsigned int get_width() { return width_; }
    unsigned int get_height() { return height_; }
    pixel_format get_pixelformat() { return pixel_format_; }

    bool save_raw_to_stream(aeon::streams::stream_ptr stream);

private:
    common::buffer_ptr_u8 buffer_;
    unsigned int width_;
    unsigned int height_;
    pixel_format pixel_format_;
};

using image_ptr = std::shared_ptr<image>;

} // namespace resources
} // namespace aeon
