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

#include <aeon/platform.h>
#include <aeon/streams.h>
#include <aeon/utility.h>
#include <resources/resource_manager.h>
#include <resources/codecs/shader_codec.h>
#include <resources/wrappers/shader_resource_wrapper.h>
#include <common/buffer.h>

namespace aeon
{
namespace resources
{

resource_encoding shader_codec::get_codec_type() const
{
    return resource_encoding::material;
}

shader_ptr shader_codec::decode(resource_manager &parent, shader_resource_wrapper_ptr wrapper)
{
    return nullptr;
}

} // namespace resources
} // namespace aeon
