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

#include <resources/codec_metadata.h>
#include <resources/resource_interface.h>
#include <resources/resource_type.h>
#include <resources/resource_encoding.h>
#include <resources/resource_provider.h>
#include <memory>
#include <string>

namespace aeon
{
namespace resources
{

DEFINE_EXCEPTION_OBJECT(resource_exception, aeon::common::exception,
    "Generic Resource exception.");
DEFINE_EXCEPTION_OBJECT(resource_closed_exception, resource_exception,
    "Resource is no longer available. It may have been unmounted.");
DEFINE_EXCEPTION_OBJECT(resource_type_exception, resource_exception,
    "Unknown resource encoding or type.");

class resource
{
friend class resource_interface;
friend class resource_manager;
public:
    virtual ~resource();

    resource_interface_ptr open();

    resource_interface_ptr open_raw();

    resource_type get_type() const;

private:
    resource(resource_manager &parent, const std::string &path, resource_provider_weak_ptr provider);

    void __read_raw(common::buffer_u8 &buffer);

    void __decode(common::buffer_u8 &input, common::buffer_u8 &output, codec_metadata &metadata);

    resource_manager &parent_;
    std::string path_;
    resource_provider_weak_ptr provider_;
    resource_encoding encoding_;
};

using resource_ptr = std::shared_ptr<resource>;

} // namespace resources
} // namespace aeon
