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

#include <platform/platform_filesystem_interface.h>
#include <resources/providers/filesystem_provider.h>
#include <resources/resource_manager.h>

namespace aeon
{
namespace resources
{

static std::string __get_real_path(const std::string &base, const std::string &path)
{
    return base + "/" + path;
}

filesystem_provider::filesystem_provider(const std::string &base_path)
    : resource_provider()
    , logger_(common::logger::get_singleton(), "Resources::FilesystemProvider")
    , base_path_(base_path)
{
    AEON_LOG_TRACE(logger_) << "Created Filesystem Provider for base path: '" << base_path << "'." << std::endl;
}

filesystem_provider::~filesystem_provider()
{
    AEON_LOG_TRACE(logger_) << "Deleted Filesystem Provider for base path: '" << base_path_ << "'." << std::endl;
}

bool filesystem_provider::exists(const std::string &path)
{
    platform::platform_interface &platform = __get_resource_manager()->get_platform_interface();
    platform::platform_filesystem_interface *filesystem_interface = platform.get_filesystem_interface();
    return filesystem_interface->exists(__get_real_path(base_path_, path));
}

std::vector<resource_node> filesystem_provider::list(const std::string & /*path*/)
{
    AEON_LOG_ERROR(logger_) << "List method is not implemented yet." << std::endl;
    throw std::runtime_error("Not yet implemented.");
}

void filesystem_provider::read(const std::string &path, common::buffer_u8 &buffer)
{
    AEON_LOG_TRACE(logger_) << "Read file at '" << path << "'." << std::endl;

    std::string p = __get_real_path(base_path_, path);

    platform::platform_interface &platform = __get_resource_manager()->get_platform_interface();
    platform::platform_filesystem_interface *filesystem_interface = platform.get_filesystem_interface();

    if (!filesystem_interface->exists(p))
    {
        AEON_LOG_ERROR(logger_) << "Could not read file at '" << path << "'. File does not exist." << std::endl;
        throw filesystem_provider_read_exception();
    }

    platform::platform_file_interface_ptr file =
        filesystem_interface->open_file(p, platform::file_open_mode::read | platform::file_open_mode::binary);

    common::buffer_u8 read_buffer;
    file->read(read_buffer);
    buffer = std::move(read_buffer);
}

resource_encoding filesystem_provider::get_encoding(const std::string &path) const
{
    std::string::size_type offset = path.find_last_of('.');

    if (offset == std::string::npos)
        throw filesystem_provider_type_exception();

    std::string extension = path.substr(offset + 1);

    if (extension == "amf")
        return resource_encoding::material;
    if (extension == "prg")
        return resource_encoding::shader;
    if (extension == "ata")
        return resource_encoding::atlas;
    if (extension == "png")
        return resource_encoding::image_png;

    throw filesystem_provider_type_exception();
}

} // namespace resources
} // namespace aeon
