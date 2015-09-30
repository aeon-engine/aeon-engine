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

#include <resources/exceptions.h>
#include <resources/image_codec.h>

namespace aeon
{
namespace resources
{

class image_codec_png : public image_codec
{
public:
    image_codec_png();
    ~image_codec_png() override;


    image_ptr decode(common::buffer_u8 &input) override;
    resource_encoding get_codec_type() const override;
};

} // namespace resources
} // namespace aeon
