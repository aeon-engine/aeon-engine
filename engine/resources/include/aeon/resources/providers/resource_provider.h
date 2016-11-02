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

#include <aeon/resources/resource_encoding.h>
#include <aeon/resources/exceptions.h>
#include <vector>
#include <string>
#include <memory>

namespace aeon
{
namespace resources
{

DEFINE_EXCEPTION_OBJECT(resource_provider_exception, resource_exception, "Generic Resource Provider exception.");

enum class resource_node_type
{
    file,
    directory
};

class resource_node
{
public:
    explicit resource_node(const std::string &name_, resource_node_type type_)
        : name(name_)
        , type(type_)
    {
    }

    std::string name;
    resource_node_type type;
};

class resource_manager;
class resource_provider
{
    friend class resource_manager;

public:
    resource_provider()
        : manager_(nullptr)
    {
    }

    virtual ~resource_provider() = default;

    virtual bool exists(const std::string &path) = 0;

    virtual std::vector<resource_node> list(const std::string &path) = 0;

    virtual void read(const std::string &path, std::vector<std::uint8_t> &buffer) = 0;

    virtual resource_encoding get_encoding(const std::string &path) const = 0;

protected:
    resource_manager *__get_resource_manager() const
    {
        return manager_;
    }

private:
    resource_manager *manager_;
};

} // namespace resources
} // namespace aeon
