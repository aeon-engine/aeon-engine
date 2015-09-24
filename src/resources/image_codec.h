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

#pragma once

#include <common/exception.h>
#include <common/buffer.h>
#include <resources/resource_encoding.h>
#include <resources/codec.h>
#include <resources/image.h>

namespace aeon
{
namespace resources
{

DEFINE_EXCEPTION_OBJECT(image_codec_decode_exception, codec_decode_exception,
    "Error while decoding resource.");

class image;
using image_ptr = std::shared_ptr<image>;

class image_codec : codec
{
public:
    image_codec() {}
    virtual ~image_codec() {}

    virtual image_ptr decode(common::buffer_u8 &input) = 0;
};

using image_codec_ptr = std::shared_ptr<image_codec>;

} // namespace resources
} // namespace aeon
