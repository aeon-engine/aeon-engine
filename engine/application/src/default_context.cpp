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

#include <aeon/application/default_context.h>
#include <aeon/io/generic/io_generic_filesystem_interface.h>
#include <aeon/gfx/gl/gfx_gl_device.h>
#include <aeon/platform/glfw/glfw_platform_manager.h>
#include <aeon/scene/basic_scene_manager/basic_scene_manager.h>

#include <aeon/codecs/amf_codec.h>
#include <aeon/codecs/asc_codec.h>
#include <aeon/codecs/assimp_codec.h>
#include <aeon/codecs/ata_codec.h>
#include <aeon/codecs/dds_codec.h>
#include <aeon/codecs/png_codec.h>
#include <aeon/codecs/prg_codec.h>

#include <build_config.h>

namespace aeon
{
namespace application
{

auto default_context::create() -> context
{
    auto logger_backend = create_logging_backend();
    auto logger = logger::logger(*logger_backend, "default_context");

    auto io_interface =
        std::make_unique<io::io_interface>(std::make_unique<io::generic::io_generic_filesystem_interface>());

    auto config_file = create_config_file(*io_interface, logger);

    auto input_handler = std::make_unique<input::input_handler>();
    auto device = std::make_unique<gfx::gl::gfx_gl_device>(*io_interface);

    auto platform_manager = std::make_unique<platform::glfw::glfw_platform_manager>(*input_handler, *device);
    auto resource_manager = std::make_unique<resources::resource_manager>(*io_interface);
    auto scene_manager = std::make_unique<scene::basic_scene_manager>(*device);
    auto codec_manager = create_codec_manager();
    auto asset_manager = std::make_unique<assets::asset_manager>(*codec_manager, *resource_manager, *scene_manager);

    return context{std::move(logger_backend),   std::move(config_file),   std::move(io_interface),
                   std::move(input_handler),    std::move(device),        std::move(platform_manager),
                   std::move(resource_manager), std::move(scene_manager), std::move(codec_manager),
                   std::move(asset_manager)};
}

auto default_context::create_logging_backend() -> std::unique_ptr<common::logger>
{
    auto logger_backend = std::make_unique<common::logger>();
    logger_backend->set_log_level(AEON_DEFAULT_LOG_LEVEL);
    return logger_backend;
}

auto default_context::create_config_file(io::io_interface &io_interface, logger::logger &logger)
    -> std::unique_ptr<utility::configfile>
{
    try
    {
        auto config_file = std::make_unique<utility::configfile>();
        auto file_interface = io_interface.get_filesystem_interface().open_file(
            AEON_CONFIG_FILE_NAME, io::file_open_mode::binary | io::file_open_mode::read);
        config_file->load(*file_interface);
        return config_file;
    }
    catch (utility::configfile_exception &)
    {
        AEON_LOG_ERROR(logger) << "Error while parsing config file." << std::endl;
    }
    catch (io::io_file_exception &)
    {
        AEON_LOG_ERROR(logger) << "Error while reading config file." << std::endl;
    }

    throw context_exception();
}

auto default_context::create_codec_manager() -> std::unique_ptr<codecs::codec_manager>
{
    auto codec_manager = std::make_unique<codecs::codec_manager>();

    codec_manager->register_codec(
        std::make_unique<codecs::basic_codec_factory<codecs::material_codec_amf>>(resources::resource_encoding("amf")));
    codec_manager->register_codec(
        std::make_unique<codecs::basic_codec_factory<codecs::scene_codec_asc>>(resources::resource_encoding("asc")));
    codec_manager->register_codec(
        std::make_unique<codecs::basic_codec_factory<codecs::mesh_codec_assimp>>(resources::resource_encoding("dae")));
    codec_manager->register_codec(
        std::make_unique<codecs::basic_codec_factory<codecs::atlas_codec_ata>>(resources::resource_encoding("ata")));
    codec_manager->register_codec(
        std::make_unique<codecs::basic_codec_factory<codecs::image_codec_dds>>(resources::resource_encoding("dds")));
    codec_manager->register_codec(
        std::make_unique<codecs::basic_codec_factory<codecs::image_codec_png>>(resources::resource_encoding("png")));
    codec_manager->register_codec(
        std::make_unique<codecs::basic_codec_factory<codecs::shader_codec_prg>>(resources::resource_encoding("prg")));

    return codec_manager;
}

} // namespace application
} // namespace aeon
