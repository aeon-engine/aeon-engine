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

#include <aeon/resources/providers/resource_provider.h>
#include <aeon/resources/resource_encoding.h>
#include <aeon/resources/exceptions.h>
#include <vector>
#include <string>

namespace aeon
{
namespace resources
{

// resourcefile_provider
DEFINE_EXCEPTION_OBJECT(resourcefile_provider_exception, resource_provider_exception,
                        "ResourceFile Provider exception.");

DEFINE_EXCEPTION_OBJECT(resourcefile_provider_not_implemented_exception, resourcefile_provider_exception,
                        "ResourceFile Provider not implemented exception.");

class resourcefile_provider : public resource_provider
{
public:
    explicit resourcefile_provider(const std::string &base_path);
    virtual ~resourcefile_provider() = default;

private:
    auto exists(const std::string &path) const -> bool override;
    auto list(const std::string &path) const -> std::vector<resource_node> override;
    void read(const std::string &path, std::vector<std::uint8_t> &buffer) override;
    auto get_encoding(const std::string &path) const -> resource_encoding override;

    std::string base_path_;
};

} // namespace resources
} // namespace aeon
