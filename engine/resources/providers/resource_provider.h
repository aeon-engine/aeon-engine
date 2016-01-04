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

#include <resources/resource_encoding.h>
#include <common/buffer.h>
#include <resources/exceptions.h>
#include <vector>
#include <string>
#include <memory>

namespace aeon
{
namespace resources
{

enum class resource_node_type
{
    file,
    directory
};

class resource_node
{
public:
    resource_node(const std::string &name_, resource_node_type type_)
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

    virtual void read(const std::string &path, common::buffer_u8 &buffer) = 0;

    virtual resource_encoding get_encoding(const std::string &path) const = 0;

protected:
    resource_manager *get_resource_manager()
    {
        return manager_;
    }

private:
    resource_manager *manager_;
};

using resource_provider_ptr = std::shared_ptr<resource_provider>;
using resource_provider_weak_ptr = std::weak_ptr<resource_provider>;

} // namespace resources
} // namespace aeon
