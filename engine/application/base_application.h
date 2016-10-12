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
#include <aeon/resources/resource_manager.h>
#include <aeon/assets/asset_manager.h>
#include <aeon/gfx/gfx_window.h>
#include <aeon/platform/platform_filesystem_interface.h>
#include <aeon/platform/platform_file_interface.h>
#include <aeon/platform/generic/platform_generic_filesystem_interface.h>
#include <aeon/common/logger.h>
#include <aeon/utility.h>
#include <buildinfo.h>

namespace aeon
{

/*!
 * Generic base class for games with a single render window. This saves the user
 * from having to instantiate and initialize all the required core engine components.
 *
 * It's possible to use the engine without using this class. In that case all core
 * components (like platform, gfx, resource manager, etc.) must be initialized manually.
 */
template <typename device_t, typename scene_manager_t>
class base_application
{
public:
    /*!
     * Constructor
     * \param argc Argument count (like main)
     * \param argv Arguments (like main)
     * \param default_width The default width of the render window if the value is missing from the config file.
     * \param default_height The default height of the render window if the value is missing from the config file.
     * \param window_title The title of the window (may not be shown on some platforms)
     */
    explicit base_application(const int default_width, const int default_height, const std::string &window_title)
        : logger_backend_()
        , logger_(common::logger::get_singleton(), "Application")
        , config_file_()
        , platform_(std::make_unique<platform::generic::platform_filesystem_interface>())
        , device_(platform_)
        , resource_manager_(platform_)
        , scene_manager_(device_)
        , asset_manager_(resource_manager_, scene_manager_)
        , window_(nullptr)
    {
        AEON_LOG_MESSAGE(logger_) << "Initializing Aeon Engine (" << buildinfo::full_version << ", "
                                  << buildinfo::build_date << ")." << std::endl;

        // Init opengl
        device_.initialize();

        __load_config_file();
        __create_window(default_width, default_height, window_title);
    }

    /*!
     * Destructor
     */
    virtual ~base_application() = default;

    /*!
     * Get the main window created for this application.
     */
    gfx::gfx_window_ptr get_main_window() const
    {
        return window_;
    }

    /*!
     * Get a pointer to the scene manager.
     */
    scene_manager_t *get_scene_manager()
    {
        return &scene_manager_;
    }

    /*!
     * Get a pointer to the resource manager. The resource manager can be used
     * for loading raw data like images.
     */
    resources::resource_manager *get_resource_manager()
    {
        return &resource_manager_;
    }

    /*!
     * Get a pointer to the asset manager. The asset manager can be used for
     * loading raw data into usable assets like textures.
     */
    assets::asset_manager &get_asset_manager()
    {
        return asset_manager_;
    }

    /*!
     * Get a pointer to the platform interface. The platform interface can be
     * used to perform all sorts of generic platform specific operations, like
     * file IO.
     */
    platform::platform_interface *get_platform_interface()
    {
        return &platform_;
    }

    /*!
     * Get a pointer to the main logger backend. Logging through this backend
     * will log to the console log.
     */
    aeon::logger::logger &get_logger()
    {
        return logger_;
    }

private:
    /*!
     * Try to load the config.conf file. Will log an error to the console if it could not be loaded or parsed.
     * In this case, default values will be used.
     */
    void __load_config_file()
    {
        try
        {
            platform::platform_file_interface_ptr file_interface = platform_.get_filesystem_interface().open_file(
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

    /*!
     * Create the main render window
     * \param default_width The default width of the window if the value is missing from the config file.
     * \param default_height The default height of the window if the value is missing from the config file.
     * \param title The window title. This title may not be shown on certain platforms.
     */
    void __create_window(const int default_width, const int default_height, const std::string &title)
    {
        const int width = config_file_.get<int>("window_width", default_width);
        const int height = config_file_.get<int>("window_height", default_height);
        const int multisample = config_file_.get<int>("multisample", 0);
        const bool double_buffer = config_file_.get<bool>("double_buffer", true);

        gfx::gfx_window_settings settings(width, height, title);
        settings.set_multisample(multisample);
        settings.set_buffer_mode(double_buffer ? gfx::buffer_mode::double_buffer : gfx::buffer_mode::single_buffer);

        window_ = device_.create_window(settings);
    }

protected:
    common::logger logger_backend_;
    aeon::logger::logger logger_;

    utility::configfile config_file_;

    platform::platform_interface platform_;
    device_t device_;

    resources::resource_manager resource_manager_;
    scene_manager_t scene_manager_;
    assets::asset_manager asset_manager_;

    gfx::gfx_window_ptr window_;
};

} // namespace aeon
