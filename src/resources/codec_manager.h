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
#include <aeon/utility.h>
#include <resources/resource_encoding.h>
#include <resources/codec.h>

namespace aeon
{
namespace resources
{

DEFINE_EXCEPTION_OBJECT(codec_manager_exception, aeon::common::exception,
    "Generic Codec Manager exception.");

DEFINE_EXCEPTION_OBJECT(codec_manager_unknown_codec_exception, codec_manager_exception,
    "Unknown or unsupported codec requested from codec manager.");

class codec_manager
{
using codec_map = utility::linear_map<resource_encoding, codec_ptr>;

public:
    codec_manager();
    ~codec_manager();

    void decode(common::buffer_u8 &input, resource_encoding encoding, common::buffer_u8 &output, codec_metadata &metadata);

private:
    codec_map codecs_;
};

} // namespace resources
} // namespace aeon
