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

#include <aeon/resources/exceptions.h>
#include <aeon/resources/codecs/image_codec.h>
#include <aeon/common/logger.h>

namespace aeon
{
namespace resources
{

DEFINE_EXCEPTION_OBJECT(codec_dds_decode_exception, codec_decode_exception, "Error while decoding DDS image resource.");

class image_codec_dds : public image_codec
{
public:
    image_codec_dds();
    virtual ~image_codec_dds() = default;

    auto decode(resource_manager &parent, const std::shared_ptr<image_resource_wrapper> &wrapper) const
        -> std::shared_ptr<image> override;
    auto get_codec_type() const -> resource_encoding override;

private:
    mutable logger::logger logger_;
};

} // namespace resources
} // namespace aeon