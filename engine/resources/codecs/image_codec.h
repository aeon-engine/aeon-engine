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

#include <resources/exceptions.h>
#include <common/buffer.h>
#include <resources/resource_encoding.h>
#include <resources/codecs/codec.h>
#include <resources/image.h>

namespace aeon
{
namespace resources
{

class image;
class image_resource_wrapper;

class image_codec : public codec
{
public:
    image_codec() = default;
    virtual ~image_codec() = default;

    virtual image_ptr decode(image_resource_wrapper_ptr wrapper) = 0;
};

using image_codec_ptr = std::unique_ptr<image_codec>;

} // namespace resources
} // namespace aeon
