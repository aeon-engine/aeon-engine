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

#include <resources/resource_manager.h>
#include <resources/resource_interface.h>
#include <resources/resource.h>
#include <resources/resource_provider.h>
#include <resources/codec_metadata.h>

namespace aeon
{
namespace resources
{

resource::resource(resource_manager &parent, const std::string &path, resource_provider_weak_ptr provider) :
    parent_(parent),
    path_(path),
    provider_(provider),
    encoding_(resource_encoding::unknown)
{
    if (auto p = provider.lock())
    {
        encoding_ = p->get_encoding(path);
    }
}

resource::~resource()
{
}

resource_interface_ptr resource::open()
{
    common::buffer_u8 raw_buffer;
    __read_raw(raw_buffer);

    common::buffer_u8 decoded_buffer;
    codec_metadata decoded_metadata;
    __decode(raw_buffer, decoded_buffer, decoded_metadata);

    // Note: we can not use make_shared due to private constructor
    return resource_interface_ptr(new resource_interface(*this, std::move(raw_buffer)));
}

resource_interface_ptr resource::open_raw()
{
    common::buffer_u8 raw_buffer;
    __read_raw(raw_buffer);

    // Note: we can not use make_shared due to private constructor
    return resource_interface_ptr(new resource_interface(*this, std::move(raw_buffer)));
}

resource_type resource::get_type() const
{
    switch (encoding_)
    {
        case resource_encoding::image_png:
            return resource_type::image;
        case resource_encoding::unknown:
        default:
            throw resource_type_exception();
    }
}

void resource::__read_raw(common::buffer_u8 &buffer)
{
    auto p = provider_.lock();

    if (!p)
        throw resource_closed_exception();

    p->read(path_, buffer);
}

void resource::__decode(common::buffer_u8 &input, common::buffer_u8 &output, codec_metadata &metadata)
{
    if (encoding_ == resource_encoding::unknown)
        throw resource_type_exception();

    parent_.get_codec_manager().decode(input, encoding_, output, metadata);
}

} // namespace resources
} // namespace aeon
