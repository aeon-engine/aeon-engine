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
#include <aeon/resources/resource_encoding.h>
#include <memory>

namespace aeon
{
namespace resources
{

// codec
DEFINE_EXCEPTION_OBJECT(codec_exception, resource_exception, "Generic Codec exception.");
DEFINE_EXCEPTION_OBJECT(codec_decode_exception, codec_exception, "Error while decoding resource.");

class codec
{
public:
    codec() = default;
    virtual ~codec() = default;

    virtual resource_encoding get_codec_type() const = 0;
};

} // namespace resources
} // namespace aeon
