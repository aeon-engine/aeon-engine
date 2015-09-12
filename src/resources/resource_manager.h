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

#include <resources/codec_manager.h>
#include <resources/resource_provider.h>
#include <common/exception.h>
#include <resources/resource.h>
#include <aeon/utility.h>

namespace aeon
{
namespace resources
{

DEFINE_EXCEPTION_OBJECT(resource_manager_exception, aeon::common::exception,
    "Generic resource manager exception.");

DEFINE_EXCEPTION_OBJECT(resource_manager_mount_exception, resource_manager_exception,
    "Could not mount resource provider.");

DEFINE_EXCEPTION_OBJECT(resource_manager_duplicate_mount_exception, resource_manager_mount_exception,
    "Could not mount resource provider. Duplicate mountpoint given.");

class resource_manager
{
using mount_points = utility::linear_map<std::string, resource_provider_ptr>;

public:
    resource_manager();
    ~resource_manager();

    void mount(resource_provider_ptr provider, const std::string &mountpoint = "/");
    void unmount(const std::string &mountpoint);

    resource_ptr load(const std::string &path);

    codec_manager &get_codec_manager()
    {
        return codec_manager_;
    }

private:
    mount_points mount_points_;
    codec_manager codec_manager_;
};

} // namespace resources
} // namespace aeon
