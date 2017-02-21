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
