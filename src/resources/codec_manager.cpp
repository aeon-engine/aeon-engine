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

#include <resources/codec_manager.h>

namespace aeon
{
namespace resources
{

codec_manager::codec_manager()
{
}

codec_manager::~codec_manager()
{
}

void codec_manager::decode(common::buffer_u8& input, resource_encoding encoding, common::buffer_u8& output, codec_metadata& metadata)
{
    auto result = codecs_.find(encoding);

    if (result == codecs_.end())
        throw codec_manager_unknown_codec_exception();

    result->second->decode(input, output, metadata);
}

} // namespace resources
} // namespace aeon
