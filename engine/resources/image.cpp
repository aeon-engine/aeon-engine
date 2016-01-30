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

#include <resources/image.h>

namespace aeon
{
namespace resources
{

image::image(resource_wrapper_ptr wrapper)
    : resource(wrapper)
    , width_(0)
    , height_(0)
    , pixel_format_(pixel_format::rgba)
{
}

image::image(resource_wrapper_ptr wrapper, common::buffer_u8 &&buffer, unsigned int width, unsigned int height,
             pixel_format pixelformat /*= pixel_format::rgba*/)
    : resource(wrapper)
    , buffer_(std::move(buffer))
    , width_(width)
    , height_(height)
    , pixel_format_(pixelformat)
{
}

void image::set_data(common::buffer_u8 &&buffer, unsigned int width, unsigned int height,
                     pixel_format pixelformat /*= pixel_format::rgba*/)
{
    if (buffer.empty())
        throw image_data_exception();

    buffer_ = std::move(buffer);
    width_ = width;
    height_ = height;
    pixel_format_ = pixelformat;
}

void image::clear_data()
{
    buffer_.clear();
}

} // namespace resources
} // namespace aeon
