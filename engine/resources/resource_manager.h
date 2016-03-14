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

#include <resources/wrappers/image_resource_wrapper.h>
#include <resources/wrappers/material_resource_wrapper.h>
#include <resources/providers/resource_provider.h>
#include <resources/exceptions.h>
#include <resources/wrappers/resource_wrapper.h>
#include <aeon/utility.h>
#include <resources/codecs/codec_manager.h>
#include <platform/platform_interface.h>
#include <resources/wrappers/atlas_resource_wrapper.h>
#include <resources/atlas.h>
#include <resources/font.h>
#include <common/logger.h>
#include <map>

namespace aeon
{
namespace resources
{

class resource_wrapper;
using resource_wrapper_ptr = std::shared_ptr<resource_wrapper>;

class resource_manager
{
    using mount_points = std::map<std::string, resource_provider_ptr>;

public:
    explicit resource_manager(platform::platform_interface &platform);
    ~resource_manager();

    void mount(resource_provider_ptr provider, const std::string &mountpoint = "/");
    void unmount(const std::string &mountpoint);

    image_resource_wrapper_ptr load_image_wrapper(const std::string &path);
    material_resource_wrapper_ptr load_material_wrapper(const std::string &path);
    shader_resource_wrapper_ptr load_shader_wrapper(const std::string &path);
    atlas_resource_wrapper_ptr load_atlas_wrapper(const std::string &path);
    font_resource_wrapper_ptr load_font_wrapper(const std::string &path);

    platform::platform_interface &get_platform_interface() const
    {
        return platform_;
    }

    codec_manager &get_codec_manager()
    {
        return codec_manager_;
    }

private:
    resource_provider_ptr __find_best_match_provider(const std::string &path, std::string &provider_path);

    aeon::logger::logger logger_;
    platform::platform_interface &platform_;
    mount_points mount_points_;
    codec_manager codec_manager_;
};

} // namespace resources
} // namespace aeon
