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

#include <aeon/data/image.h>

namespace aeon
{
namespace data
{

image::image(std::vector<std::uint8_t> &&buffer, const unsigned int width, const unsigned int height,
             pixel_format pixelformat, const unsigned int mipmap_count)
    : buffer_(std::move(buffer))
    , width_(width)
    , height_(height)
    , pixel_format_(pixelformat)
    , mipmap_count_(mipmap_count)
{
}

image::image(image &&other) noexcept = default;
image &image::operator=(image &&other) noexcept = default;

bool image::has_data() const
{
    return buffer_.empty();
}

const std::vector<std::uint8_t> &image::get_data() const
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

unsigned int image::get_mipmap_count() const
{
    return mipmap_count_;
}

} // namespace data
} // namespace aeon
