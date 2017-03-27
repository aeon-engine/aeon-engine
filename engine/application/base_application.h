/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#include <aeon/resources/resource_manager.h>
#include <aeon/assets/asset_manager.h>
#include <aeon/platform/platform_window.h>
#include <aeon/io/io_filesystem_interface.h>
#include <aeon/io/io_file_interface.h>
#include <aeon/io/generic/io_generic_filesystem_interface.h>
#include <aeon/input/input_handler.h>
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
template <typename device_t, typename platform_t, typename scene_manager_t>
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
        , io_(std::make_unique<io::generic::io_filesystem_interface>())
        , input_handler_()
        , device_(io_)
        , platform_(input_handler_, device_)
        , resource_manager_(io_)
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
    auto get_main_window() const
    {
        return window_;
    }

    /*!
     * Get a pointer to the scene manager.
     */
    auto get_scene_manager()
    {
        return &scene_manager_;
    }

    /*!
     * Get a pointer to the resource manager. The resource manager can be used
     * for loading raw data like images.
     */
    auto get_resource_manager()
    {
        return &resource_manager_;
    }

    /*!
     * Get a reference to the asset manager. The asset manager can be used for
     * loading raw data into usable assets like textures.
     */
    auto &get_asset_manager()
    {
        return asset_manager_;
    }

    /*!
     * Get a pointer to the io interface. The platform interface can be
     * used to perform all sorts of generic platform specific operations, like
     * file IO.
     */
    auto get_io_interface()
    {
        return &io_;
    }

    /*!
     * Get a reference to the input handler. The input handler can be used for
     * handling generic keyboard, mouse, touch and joystick events.
     */
    auto &get_input_handler()
    {
        return input_handler_;
    }

    /*!
     * Get a reference to the main logger. Logging through this object will log to the console log.
     */
    auto &get_logger()
    {
        return logger_;
    }

    /*!
     * Get a reference to the main logger backend. This allows for selecting the log level.
     */
    auto &get_logger_backend()
    {
        return logger_backend_;
    }

    /*!
     * Get a reference to the selected graphics device. This should only be used by advanced users, and is
     * not intended for regular engine use.
     */
    auto &get_gfx_device()
    {
        return device_;
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
            auto file_interface = io_.get_filesystem_interface().open_file("config.conf", io::file_open_mode::binary |
                                                                                              io::file_open_mode::read);

            auto config_file_data = std::vector<std::uint8_t>();
            file_interface->read(config_file_data);

            config_file_.load(std::move(config_file_data));
        }
        catch (utility::configfile_exception &)
        {
            AEON_LOG_ERROR(logger_) << "Error while parsing config file." << std::endl;
        }
        catch (io::io_file_exception &)
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
        const auto width = config_file_.get<int>("window_width", default_width);
        const auto height = config_file_.get<int>("window_height", default_height);
        const auto multisample = config_file_.get<int>("multisample", 0);
        const auto double_buffer = config_file_.get<bool>("double_buffer", true);

        auto settings = platform::window_settings{width, height, title};
        settings.set_multisample(multisample);
        settings.set_buffer_mode(double_buffer ? platform::buffer_mode::double_buffer
                                               : platform::buffer_mode::single_buffer);

        window_ = platform_.create_window(settings);
    }

protected:
    common::logger logger_backend_;
    logger::logger logger_;

    utility::configfile config_file_;

    io::io_interface io_;
    input::input_handler input_handler_;
    device_t device_;
    platform_t platform_;

    resources::resource_manager resource_manager_;
    scene_manager_t scene_manager_;
    assets::asset_manager asset_manager_;

    std::shared_ptr<platform::window> window_;
};

} // namespace aeon
