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

#include <aeon/codecs/codec_manager.h>
#include <aeon/resources/resource_manager.h>
#include <aeon/assets/asset_manager.h>
#include <aeon/io/io_interface.h>
#include <aeon/input/input_handler.h>
#include <aeon/platform/platform_manager.h>
#include <aeon/scene/scene_manager.h>
#include <aeon/common/logger.h>
#include <aeon/utility/configfile.h>

namespace aeon::application
{

class context
{
public:
    explicit context(std::unique_ptr<logger::base_backend> logger_backend,
                     std::unique_ptr<utility::configfile> config_file, std::unique_ptr<io::io_interface> io_interface,
                     std::unique_ptr<input::input_handler> input_handler, std::unique_ptr<gfx::device> device,
                     std::unique_ptr<platform::platform_manager> platform_manager,
                     std::unique_ptr<resources::resource_manager> resource_manager,
                     std::unique_ptr<scene::scene_manager> scene_manager,
                     std::unique_ptr<codecs::codec_manager> codec_manager,
                     std::unique_ptr<assets::asset_manager> asset_manager)
        : logger_backend(std::move(logger_backend))
        , config_file(std::move(config_file))
        , io_interface(std::move(io_interface))
        , input_handler(std::move(input_handler))
        , device(std::move(device))
        , platform_manager(std::move(platform_manager))
        , resource_manager(std::move(resource_manager))
        , scene_manager(std::move(scene_manager))
        , codec_manager(std::move(codec_manager))
        , asset_manager(std::move(asset_manager))
    {
    }

    context(const context &) noexcept = delete;
    auto operator=(const context &) noexcept -> context & = delete;

    context(context &&) noexcept = default;
    auto operator=(context &&) noexcept -> context & = default;

    std::unique_ptr<logger::base_backend> logger_backend;
    std::unique_ptr<utility::configfile> config_file;
    std::unique_ptr<io::io_interface> io_interface;
    std::unique_ptr<input::input_handler> input_handler;
    std::unique_ptr<gfx::device> device;
    std::unique_ptr<platform::platform_manager> platform_manager;
    std::unique_ptr<resources::resource_manager> resource_manager;
    std::unique_ptr<scene::scene_manager> scene_manager;
    std::unique_ptr<codecs::codec_manager> codec_manager;
    std::unique_ptr<assets::asset_manager> asset_manager;
};

} // namespace aeon::application
