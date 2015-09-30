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
#include <resources/resource.h>
#include <resources/resource_provider.h>

namespace aeon
{
namespace resources
{

resource::resource(resource_manager &parent, const std::string &path,\
                   resource_provider_weak_ptr provider) :
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

resource_type resource::get_type() const
{
    return parent_.get_codec_manager().get_resource_type_by_encoding(encoding_);
}

void resource::__read_raw(common::buffer_u8 &buffer)
{
    auto p = provider_.lock();

    if (!p)
        throw resource_closed_exception();

    p->read(path_, buffer);
}

} // namespace resources
} // namespace aeon
