/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#include <aeon/resources/exceptions.h>
#include <aeon/resources/resource_type.h>
#include <aeon/resources/resource_encoding.h>
#include <aeon/resources/providers/resource_provider.h>
#include <aeon/common/logger.h>
#include <memory>
#include <string>

namespace aeon
{
namespace resources
{

// resource
DEFINE_EXCEPTION_OBJECT(resource_closed_exception, resource_exception,
                        "Resource is no longer available. It may have been unmounted.");

DEFINE_EXCEPTION_OBJECT(resource_type_exception, resource_exception,
                        "Unknown resource encoding or actual type does not match expected resource type.");

class resource_manager;
class resource_wrapper : public std::enable_shared_from_this<resource_wrapper>
{
public:
    virtual ~resource_wrapper() = default;

    auto get_type() const -> resource_type;

    auto get_encoding() const
    {
        return encoding_;
    }

    const auto &get_path() const
    {
        return path_;
    }

    void read_raw(std::vector<std::uint8_t> &buffer) const;

protected:
    explicit resource_wrapper(resource_manager &parent, const std::string &path,
                              const std::weak_ptr<resource_provider> &provider);

    auto &__get_parent() const
    {
        return parent_;
    }

    auto __get_provider() const
    {
        return provider_;
    }

private:
    aeon::logger::logger logger_;
    resource_manager &parent_;
    std::string path_;
    std::weak_ptr<resource_provider> provider_;
    resource_encoding encoding_;
};

} // namespace resources
} // namespace aeon
