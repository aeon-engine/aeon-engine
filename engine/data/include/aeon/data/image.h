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

#include <aeon/math/vector2.h>
#include <vector>
#include <cstdint>

namespace aeon
{
namespace data
{

class image
{
public:
    enum class pixel_format
    {
        rgb,
        rgba,
        dxt1,
        dxt3,
        dxt5
    };

    explicit image(std::vector<std::uint8_t> &&buffer, const unsigned int width, const unsigned int height,
                   pixel_format pixelformat = pixel_format::rgba, const unsigned int mipmap_count = 0);

    ~image() = default;

    image(const image &) noexcept = delete;
    auto operator=(const image &) noexcept -> image & = delete;

    image(image &&) noexcept = default;
    auto operator=(image &&) noexcept -> image & = default;

    auto has_data() const -> bool;

    auto get_data() const -> const std::vector<std::uint8_t> &;

    auto get_width() const -> unsigned int;

    auto get_height() const -> unsigned int;

    auto get_size() const -> math::vector2<float>;

    auto get_pixelformat() const -> pixel_format;

    auto get_mipmap_count() const -> unsigned int;

private:
    std::vector<std::uint8_t> buffer_;
    unsigned int width_;
    unsigned int height_;
    pixel_format pixel_format_;
    unsigned int mipmap_count_;
};

} // namespace data
} // namespace aeon
