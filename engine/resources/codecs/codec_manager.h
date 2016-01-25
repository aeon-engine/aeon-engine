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
#include <aeon/utility.h>
#include <resources/resource_encoding.h>
#include <resources/resource_type.h>
#include <resources/codecs/codec.h>
#include <resources/codecs/image_codec.h>
#include <map>

namespace aeon
{
namespace resources
{

class codec_manager
{
    using codec_map = std::map<resource_encoding, codec_ptr>;

public:
    codec_manager();
    ~codec_manager();

    codec_ptr get_codec(resource_encoding encoding);
    image_codec_ptr get_image_codec(resource_encoding encoding);

    resource_type get_resource_type_by_encoding(resource_encoding encoding) const;

private:
    void __register_codecs();

    codec_map codecs_;
};

} // namespace resources
} // namespace aeon
