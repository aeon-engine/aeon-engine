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

#include <resources/codec/image_codec.h>
#include <resources/image.h>

namespace aeon
{
namespace resources
{

class image_codec_png : public image_codec
{
public:
    image_codec_png();
    virtual ~image_codec_png();

    virtual image_ptr decode(aeon::streams::stream_ptr stream);
    virtual std::string get_type_name() const;
};

} // namespace resources
} // namespace aeon
