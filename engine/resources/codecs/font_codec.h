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
#include <resources/wrappers/font_resource_wrapper.h>
#include <resources/codecs/codec.h>
#include <resources/font.h>

namespace aeon
{
namespace resources
{

class resource_manager;

class font_codec : public codec
{
public:
    font_codec() = default;
    virtual ~font_codec() = default;

    virtual font_ptr decode(resource_manager &parent, font_resource_wrapper_ptr wrapper) = 0;
};

using font_codec_ptr = std::unique_ptr<font_codec>;

} // namespace resources
} // namespace aeon
