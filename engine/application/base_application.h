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
#include <resources/resource_manager.h>
#include <assets/asset_manager.h>
#include <platform/platform_window.h>
#include <platform/platform_filesystem_interface.h>
#include <platform/platform_file_interface.h>
#include <common/logger.h>
#include <aeon/utility.h>
#include <buildinfo.h>

namespace aeon
{

template <typename platform_interface_t, typename device_t, typename scene_manager_t>
class base_application
{
public:
    explicit base_application(int argc, char *argv[], const int default_width, const int default_height,
                              const std::string &window_title)
        : logger_backend_()
        , logger_(common::logger::get_singleton(), "Application")
        , config_file_()
        , platform_(argc, argv)
        , resource_manager_(platform_)
        , scene_manager_(device_)
        , asset_manager_(resource_manager_, scene_manager_)
        , window_(nullptr)
    {
        AEON_LOG_MESSAGE(logger_) << "Initializing Aeon Engine (" << buildinfo::full_version << ", "
                                  << buildinfo::build_date << ")." << std::endl;

        // Init the platform and window
        platform_.initialize();

        __load_config_file();
        __create_window(default_width, default_height, window_title);

        // Init opengl
        device_.initialize();
    }

    virtual ~base_application() = default;

    platform::platform_window_ptr get_main_window() const
    {
        return window_;
    }

    scene_manager_t *get_scene_manager()
    {
        return &scene_manager_;
    }

    resources::resource_manager *get_resource_manager()
    {
        return &resource_manager_;
    }

    assets::asset_manager &get_asset_manager()
    {
        return asset_manager_;
    }

    platform_interface_t *get_platform_interface()
    {
        return &platform_;
    }

    aeon::logger::logger &get_logger()
    {
        return logger_;
    }

private:
    void __load_config_file()
    {
        try
        {
            platform::platform_file_interface_ptr file_interface = platform_.get_filesystem_interface()->open_file(
                "config.conf", platform::file_open_mode::binary | platform::file_open_mode::read);

            common::buffer_u8 config_file_data;
            file_interface->read(config_file_data);

            config_file_.load(std::move(config_file_data));
        }
        catch (utility::configfile_exception &)
        {
            AEON_LOG_ERROR(logger_) << "Error while parsing config file." << std::endl;
        }
        catch (platform::platform_file_exception &)
        {
            AEON_LOG_ERROR(logger_) << "Error while reading config file." << std::endl;
        }
    }

    void __create_window(const int default_width, const int default_height, const std::string &title)
    {
        const int width = config_file_.get<int>("window_width", default_width);
        const int height = config_file_.get<int>("window_height", default_height);
        window_ = platform_.create_window(width, height, title);
    }

protected:
    common::logger logger_backend_;
    aeon::logger::logger logger_;

    utility::configfile config_file_;

    platform_interface_t platform_;
    device_t device_;

    resources::resource_manager resource_manager_;
    scene_manager_t scene_manager_;
    assets::asset_manager asset_manager_;

    platform::platform_window_ptr window_;
};

} // namespace aeon
