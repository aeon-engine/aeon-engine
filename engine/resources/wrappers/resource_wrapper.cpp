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

#include <resources/resource_manager.h>
#include <resources/wrappers/resource_wrapper.h>
#include <resources/providers/resource_provider.h>

namespace aeon
{
namespace resources
{

resource_wrapper::resource_wrapper(resource_manager &parent, const std::string &path,
                                   resource_provider_weak_ptr provider)
    : logger_(common::logger::get_singleton(), "Resources::ResourceWrapper")
    , parent_(parent)
    , path_(path)
    , provider_(provider)
    , encoding_(resource_encoding::unknown)
{
    if (auto p = provider.lock())
    {
        encoding_ = p->get_encoding(path);
    }
}

resource_type resource_wrapper::get_type() const
{
    return parent_.get_codec_manager().get_resource_type_by_encoding(encoding_);
}

void resource_wrapper::read_raw(common::buffer_u8 &buffer)
{
    auto p = provider_.lock();

    if (!p)
    {
        AEON_LOG_FATAL(logger_) << "Failed to read resource at " << path_ << ". Provider not available." << std::endl;
        throw resource_closed_exception();
    }

    p->read(path_, buffer);
}

} // namespace resources
} // namespace aeon
