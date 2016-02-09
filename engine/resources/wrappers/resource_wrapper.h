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
#include <resources/resource_type.h>
#include <resources/resource_encoding.h>
#include <resources/providers/resource_provider.h>
#include <memory>
#include <string>

namespace aeon
{
namespace resources
{

class resource_manager;
class resource_wrapper : public std::enable_shared_from_this<resource_wrapper>
{
public:
    virtual ~resource_wrapper() = default;

    resource_type get_type() const;

    resource_encoding get_encoding() const
    {
        return encoding_;
    }

    const std::string &get_path() const
    {
        return path_;
    }

    void read_raw(common::buffer_u8 &buffer);

protected:
    explicit resource_wrapper(resource_manager &parent, const std::string &path, resource_provider_weak_ptr provider);

    resource_manager &__get_parent() const
    {
        return parent_;
    }

    resource_provider_weak_ptr __get_provider() const
    {
        return provider_;
    }

private:
    resource_manager &parent_;
    std::string path_;
    resource_provider_weak_ptr provider_;
    resource_encoding encoding_;
};

using resource_wrapper_ptr = std::shared_ptr<resource_wrapper>;

} // namespace resources
} // namespace aeon
