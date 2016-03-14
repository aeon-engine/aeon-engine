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
#include <resources/codecs/font_codec.h>
#include <common/logger.h>

namespace aeon
{
namespace resources
{

class font_codec_freetype : public font_codec
{
public:
    font_codec_freetype();
    virtual ~font_codec_freetype() = default;

    font_ptr decode(resource_manager &parent, font_resource_wrapper_ptr wrapper) override;
    resource_encoding get_codec_type() const override;

private:
    aeon::logger::logger logger_;
};

} // namespace resources
} // namespace aeon
