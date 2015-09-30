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

#include <resources/exceptions.h>
#include <resources/resource_type.h>
#include <resources/resource_encoding.h>
#include <resources/resource_provider.h>
#include <memory>
#include <string>

namespace aeon
{
namespace resources
{

class resource_manager;
class resource
{
friend class resource_interface;
friend class resource_manager;
public:
    virtual ~resource();

    resource_type get_type() const;
    resource_encoding get_encoding() const { return encoding_; }

protected:
    resource(resource_manager &parent, const std::string &path,
        resource_provider_weak_ptr provider);

    resource_manager &__get_parent() { return parent_; }
    resource_provider_weak_ptr __get_provider() { return provider_; }
    void __read_raw(common::buffer_u8 &buffer);

private:
    resource_manager &parent_;
    std::string path_;
    resource_provider_weak_ptr provider_;
    resource_encoding encoding_;
};

using resource_ptr = std::shared_ptr<resource>;

} // namespace resources
} // namespace aeon
