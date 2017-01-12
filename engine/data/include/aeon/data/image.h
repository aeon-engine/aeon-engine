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

#pragma once

#include <aeon/utility.h>
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
        dxt1,
        dxt3,
        dxt5
    };

    explicit image(std::vector<std::uint8_t> &&buffer, const unsigned int width, const unsigned int height,
                   pixel_format pixelformat = pixel_format::rgba, const unsigned int mipmap_count = 0);

    ~image() = default;

    image(image &&other) noexcept;
    image &operator=(image &&other) noexcept;

    bool has_data() const;

    const std::vector<std::uint8_t> &get_data() const;

    unsigned int get_width() const;

    unsigned int get_height() const;

    glm::vec2 get_size() const;

    pixel_format get_pixelformat() const;

    unsigned int get_mipmap_count() const;

private:
    std::vector<std::uint8_t> buffer_;
    unsigned int width_;
    unsigned int height_;
    pixel_format pixel_format_;
    unsigned int mipmap_count_;
};

} // namespace data
} // namespace aeon
