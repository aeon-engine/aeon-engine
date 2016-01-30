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

#include <resources/resource.h>
#include <resources/exceptions.h>
#include <resources/wrappers/image_resource_wrapper.h>
#include <common/buffer.h>
#include <memory>

namespace aeon
{
namespace resources
{

class image : public resource
{
public:
    enum class pixel_format
    {
        rgb,
        rgba,
    };

    explicit image(resource_wrapper_ptr wrapper);
    explicit image(resource_wrapper_ptr wrapper, common::buffer_u8 &&buffer, unsigned int width, unsigned int height,
          pixel_format pixelformat = pixel_format::rgba);

    virtual ~image() = default;

    void set_data(common::buffer_u8 &&buffer, unsigned int width, unsigned int height,
                  pixel_format pixelformat = pixel_format::rgba);

    bool has_data() const
    {
        return buffer_.empty();
    }

    common::buffer_u8 &get_data()
    {
        return buffer_;
    }

    unsigned int get_width() const
    {
        return width_;
    }

    unsigned int get_height() const
    {
        return height_;
    }

    pixel_format get_pixelformat() const
    {
        return pixel_format_;
    }

    void clear_data();

    image_resource_wrapper_ptr get_image_resource_wrapper()
    {
        return std::dynamic_pointer_cast<image_resource_wrapper>(get_resource_wrapper());
    }

private:
    common::buffer_u8 buffer_;
    unsigned int width_;
    unsigned int height_;
    pixel_format pixel_format_;
};

using image_ptr = std::shared_ptr<image>;

} // namespace resources
} // namespace aeon
