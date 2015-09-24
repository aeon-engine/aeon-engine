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
#include <resources/resource_type.h>
#include <resources/codec.h>
#include <resources/image_codec.h>

namespace aeon
{
namespace resources
{

DEFINE_EXCEPTION_OBJECT(codec_manager_exception, aeon::common::exception,
    "Generic Codec Manager exception.");

DEFINE_EXCEPTION_OBJECT(codec_manager_unknown_codec_exception, codec_manager_exception,
    "Unknown or unsupported codec requested from codec manager.");

DEFINE_EXCEPTION_OBJECT(codec_manager_codec_mismatch_exception, codec_manager_exception,
    "Resource encoding does not match expected resource type.");

class codec_manager
{
using codec_map = utility::linear_map<resource_encoding, codec_ptr>;

public:
    codec_manager();
    ~codec_manager();

    codec_ptr get_codec(resource_encoding encoding);
    image_codec_ptr get_image_codec(resource_encoding encoding);

    resource_type get_resource_type_by_encoding(resource_encoding encoding) const;

private:
    codec_map codecs_;
};

} // namespace resources
} // namespace aeon
