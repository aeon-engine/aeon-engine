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

#include <aeon/resources/exceptions.h>
#include <aeon/resources/codecs/image_codec.h>
#include <aeon/common/logger.h>

namespace aeon
{
namespace resources
{

DEFINE_EXCEPTION_OBJECT(codec_png_decode_exception, codec_decode_exception, "Error while decoding PNG image resource.");

class image_codec_png : public image_codec
{
public:
    image_codec_png();
    virtual ~image_codec_png() = default;

    std::shared_ptr<image> decode(resource_manager &parent,
                                  const std::shared_ptr<image_resource_wrapper> &wrapper) override;
    resource_encoding get_codec_type() const override;

private:
    aeon::logger::logger logger_;
};

} // namespace resources
} // namespace aeon
