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

#include <aeon/utility.h>
#include <aeon/common/buffer.h>
#include <memory>
#include <glm/vec2.hpp>

namespace aeon
{
namespace data
{

class image : utility::noncopyable
{
public:
    enum class pixel_format
    {
        rgb,
        rgba,
    };

    explicit image(common::buffer_u8 &&buffer, unsigned int width, unsigned int height,
                   pixel_format pixelformat = pixel_format::rgba);

    ~image() = default;

    image(image &&other);
    image &operator=(image &&other);

    bool has_data() const;

    const common::buffer_u8 &get_data() const;

    unsigned int get_width() const;

    unsigned int get_height() const;

    glm::vec2 get_size() const;

    pixel_format get_pixelformat() const;

private:
    common::buffer_u8 buffer_;
    unsigned int width_;
    unsigned int height_;
    pixel_format pixel_format_;
};

using image_ptr = std::shared_ptr<image>;

} // namespace data
} // namespace aeon
