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

#include <aeon/resources/wrappers/image_resource_wrapper.h>
#include <aeon/resources/wrappers/material_resource_wrapper.h>
#include <aeon/resources/providers/resource_provider.h>
#include <aeon/resources/exceptions.h>
#include <aeon/resources/codecs/codec_manager.h>
#include <aeon/resources/wrappers/resource_wrapper.h>
#include <aeon/utility.h>
#include <aeon/resources/codecs/codec_manager.h>
#include <aeon/platform/platform_interface.h>
#include <aeon/resources/wrappers/atlas_resource_wrapper.h>
#include <aeon/resources/wrappers/mesh_resource_wrapper.h>
#include <aeon/resources/atlas.h>
#include <aeon/common/logger.h>
#include <map>

namespace aeon
{
namespace resources
{

DEFINE_EXCEPTION_OBJECT(resource_manager_exception, resource_exception, "Generic resource manager exception.");

DEFINE_EXCEPTION_OBJECT(resource_manager_mount_exception, resource_manager_exception,
                        "Could not mount resource provider.");

DEFINE_EXCEPTION_OBJECT(resource_manager_duplicate_mount_exception, resource_manager_mount_exception,
                        "Could not mount resource provider. Duplicate mountpoint given.");

class resource_manager
{
    using mount_points = std::map<std::string, std::shared_ptr<resource_provider>>;

public:
    explicit resource_manager(platform::platform_interface &platform);
    ~resource_manager();

    void mount(const std::shared_ptr<resource_provider> &provider, const std::string &mountpoint = "/");
    void unmount(const std::string &mountpoint);

    std::shared_ptr<image_resource_wrapper> load_image_wrapper(const std::string &path);
    std::shared_ptr<material_resource_wrapper> load_material_wrapper(const std::string &path);
    std::shared_ptr<shader_resource_wrapper> load_shader_wrapper(const std::string &path);
    std::shared_ptr<atlas_resource_wrapper> load_atlas_wrapper(const std::string &path);
    std::shared_ptr<mesh_resource_wrapper> load_mesh_wrapper(const std::string &path);

    platform::platform_interface &get_platform_interface()
    {
        return platform_;
    }

    codec_manager &get_codec_manager()
    {
        return codec_manager_;
    }

private:
    std::shared_ptr<resource_provider> __find_best_match_provider(const std::string &path, std::string &provider_path);

    aeon::logger::logger logger_;
    platform::platform_interface &platform_;
    mount_points mount_points_;
    codec_manager codec_manager_;
};

} // namespace resources
} // namespace aeon
