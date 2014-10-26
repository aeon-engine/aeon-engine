/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2014 Robin Degen
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

#include "stdafx.h"

namespace aeon
{

image::image() :
    width_(0),
    height_(0),
    pixel_format_(pixel_format::rgba)
{

}

image::~image()
{

}

void image::set_data(buffer_ptr buffer, unsigned int width, 
                     unsigned int height, 
                     pixel_format pixelformat /*= pixel_format::rgba*/)
{
    if (buffer == nullptr || buffer->get() == nullptr)
    {
        console::error("[Image]: Tried creating an image from an "
            "empty buffer.");
        return;
    }

    buffer_ = buffer;
    width_ = width;
    height_ = height;
    pixel_format_ = pixelformat;
}

bool image::save_raw_to_stream(stream_ptr stream)
{
    if (!stream)
        return false;

    if (!stream->good())
        return false;

    if (!buffer_)
        return false;

    if (buffer_->get() == nullptr)
        return false;

    if (stream->write(buffer_->get(), buffer_->size()) != buffer_->size())
        return false;

    return true;
}

} /* namespace aeon */
