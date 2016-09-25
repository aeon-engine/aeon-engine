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

#include <aeon/data/image.h>

namespace aeon
{
namespace data
{

image::image(common::buffer_u8 &&buffer, unsigned int width, unsigned int height,
             pixel_format pixelformat /*= pixel_format::rgba*/)
    : buffer_(std::move(buffer))
    , width_(width)
    , height_(height)
    , pixel_format_(pixelformat)
{
}

image::image(image &&other)
    : buffer_(std::move(other.buffer_))
    , width_(std::move(other.width_))
    , height_(std::move(other.height_))
    , pixel_format_(std::move(other.pixel_format_))
{
}

image &image::operator=(image &&other)
{
    buffer_ = std::move(other.buffer_);
    width_ = std::move(other.width_);
    height_ = std::move(other.height_);
    pixel_format_ = std::move(other.pixel_format_);
    return *this;
}

bool image::has_data() const
{
    return buffer_.empty();
}

const common::buffer_u8 &image::get_data() const
{
    return buffer_;
}

unsigned int image::get_width() const
{
    return width_;
}

unsigned int image::get_height() const
{
    return height_;
}

glm::vec2 image::get_size() const
{
    return glm::vec2(width_, height_);
}

image::pixel_format image::get_pixelformat() const
{
    return pixel_format_;
}

} // namespace data
} // namespace aeon
