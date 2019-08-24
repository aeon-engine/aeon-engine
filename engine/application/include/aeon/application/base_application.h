/*
 * Copyright (c) 2012-2018 Robin Degen
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

#include <aeon/application/context.h>

namespace aeon::application
{

class base_application
{
public:
    explicit base_application(context context);
    virtual ~base_application();

    base_application(const base_application &) noexcept = delete;
    auto operator=(const base_application &) noexcept -> base_application & = delete;

    base_application(base_application &&) noexcept = default;
    auto operator=(base_application &&) noexcept -> base_application & = default;

    /*!
     * Get the scene manager.
     */
    auto &get_scene_manager()
    {
        return *scene_manager_;
    }

    /*!
     * Get the resource manager. The resource manager can be used
     * for loading raw data like images.
     */
    auto &get_resource_manager()
    {
        return *resource_manager_;
    }

    /*!
     * Get the asset manager. The asset manager can be used for
     * loading raw data into usable assets like textures.
     */
    auto &get_asset_manager()
    {
        return *asset_manager_;
    }

    /*!
     * Get the codec manager. The codec manager can be used for
     * reading and writing raw data like images.
     */
    auto &get_codec_manager()
    {
        return *codec_manager_;
    }

    /*!
     * Get the io interface. The platform interface can be
     * used to perform all sorts of generic platform specific operations, like
     * file IO.
     */
    auto &get_io_interface()
    {
        return *io_;
    }

    /*!
     * Get the input handler. The input handler can be used for
     * handling generic keyboard, mouse, touch and joystick events.
     */
    auto &get_input_handler()
    {
        return *input_handler_;
    }

    /*!
     * Get the main logger. Logging through this object will log to the console log.
     */
    auto &get_logger()
    {
        return logger_;
    }

    /*!
     * Get the main logger backend. This allows for selecting the log level.
     */
    auto &get_logger_backend()
    {
        return *logger_backend_;
    }

    /*!
     * Get the selected graphics device. This should only be used by advanced users, and is
     * not intended for regular engine use.
     */
    auto &get_gfx_device()
    {
        return *device_;
    }

    /*!
     * Get the platform interface
     */
    auto &get_platform()
    {
        return *platform_;
    }

protected:
    logger::logger logger_;

    std::unique_ptr<logger::base_backend> logger_backend_;
    std::unique_ptr<ptree::property_tree> config_file_;
    std::unique_ptr<io::io_interface> io_;
    std::unique_ptr<input::input_handler> input_handler_;
    std::unique_ptr<gfx::device> device_;
    std::unique_ptr<platform::platform_manager> platform_;
    std::unique_ptr<resources::resource_manager> resource_manager_;
    std::unique_ptr<scene::scene_manager> scene_manager_;
    std::unique_ptr<codecs::codec_manager> codec_manager_;
    std::unique_ptr<assets::asset_manager> asset_manager_;
};

} // namespace aeon::application
