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

#include <exception>
#include <console/console.h>
#include <resources/image.h>

namespace aeon
{
namespace resources
{

image::image(const std::string &path) :
    width_(0),
    height_(0),
    pixel_format_(pixel_format::rgba),
    path_(path)
{

}

image::~image()
{

}

void image::set_data(common::buffer_u8 buffer, unsigned int width,
                     unsigned int height, pixel_format pixelformat /*= pixel_format::rgba*/)
{
    if (buffer.empty())
    {
        console::error("[Image]: Tried creating an image from an empty buffer.");
        throw std::runtime_error("Tried creating an image from an empty buffer.");
    }

    buffer_ = std::move(buffer);
    width_ = width;
    height_ = height;
    pixel_format_ = pixelformat;
}

void image::clear_data()
{
    buffer_.clear();
}

bool image::save_raw_to_stream(aeon::streams::stream_ptr stream)
{
    if (!stream)
        return false;

    if (!stream->good())
        return false;

    if (buffer_.empty())
        return false;

    if (stream->write(static_cast<std::uint8_t *>(&(buffer_)[0]), buffer_.size()) != buffer_.size())
        return false;

    return true;
}

} // namespace resources
} // namespace aeon
