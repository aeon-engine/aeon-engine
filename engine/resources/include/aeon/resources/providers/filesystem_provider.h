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

#include <aeon/resources/providers/resource_provider.h>
#include <aeon/resources/resource_encoding.h>
#include <aeon/common/buffer.h>
#include <aeon/resources/exceptions.h>
#include <aeon/common/logger.h>
#include <vector>
#include <string>

namespace aeon
{
namespace resources
{

DEFINE_EXCEPTION_OBJECT(filesystem_provider_exception, resource_provider_exception, "Filesystem Provider exception.");
DEFINE_EXCEPTION_OBJECT(filesystem_provider_list_exception, filesystem_provider_exception,
                        "Filesystem Provider list exception. Can not list given path.");
DEFINE_EXCEPTION_OBJECT(
    filesystem_provider_read_exception, filesystem_provider_exception,
    "Filesystem Provider read exception. Can not read given path. Path does not exist or is unreadable.");
DEFINE_EXCEPTION_OBJECT(
    filesystem_provider_type_exception, filesystem_provider_exception,
    "Filesystem Provider type exception. Can not figure out the type of the resource. File has no extension.");

class filesystem_provider : public resource_provider
{
public:
    explicit filesystem_provider(const std::string &base_path);
    virtual ~filesystem_provider();

private:
    bool exists(const std::string &path) override;
    std::vector<resource_node> list(const std::string &path) override;
    void read(const std::string &path, common::buffer_u8 &buffer) override;
    resource_encoding get_encoding(const std::string &path) const override;

    aeon::logger::logger logger_;

    std::string base_path_;
};

} // namespace resources
} // namespace aeon