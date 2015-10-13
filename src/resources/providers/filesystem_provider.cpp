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

#include <resources/providers/filesystem_provider.h>
#include <boost/filesystem.hpp>
#include <resources/resource_manager.h>
#include <platform/platform_filesystem_interface.h>

namespace aeon
{
namespace resources
{

static boost::filesystem::path __get_real_path(boost::filesystem::path base,
    const std::string &path)
{
    boost::filesystem::path p(path);
    return base/p;
}

filesystem_provider::filesystem_provider(const std::string &base_path) :
    resource_provider(),
    base_path_(base_path)
{
}

filesystem_provider::~filesystem_provider()
{
}

bool filesystem_provider::exists(const std::string &path)
{
    return boost::filesystem::exists(__get_real_path(base_path_, path));
}

std::vector<resource_node> filesystem_provider::list(const std::string &path)
{
    boost::filesystem::path p = __get_real_path(base_path_, path);

    platform::platform_interface &platform = get_resource_manager()->get_platform_interface();
    platform::platform_filesystem_interface_ptr filesystem_interface = platform.get_filesystem_interface();

    // TODO: add feature to platform_filesystem_interface
    if (!boost::filesystem::is_directory(p))
        throw filesystem_provider_list_exception();

    platform::platform_filesystem_interface::files files = filesystem_interface->list(p.string());

    std::vector<resource_node> nodes;
    for (auto f : files)
    {
        resource_node_type type = resource_node_type::file;

        if (f.type == platform::platform_filesystem_interface::file_type::directory)
            type = resource_node_type::directory;

        nodes.push_back(resource_node(f.name, type));
    }

    return std::move(nodes);
}

void filesystem_provider::read(const std::string &path, common::buffer_u8 &buffer)
{
    boost::filesystem::path p = __get_real_path(base_path_, path);

    platform::platform_interface &platform = get_resource_manager()->get_platform_interface();
    platform::platform_filesystem_interface_ptr filesystem_interface = platform.get_filesystem_interface();

    if (filesystem_interface->exists(p.string()))
        throw filesystem_provider_read_exception();

    platform::platform_file_interface_ptr file = filesystem_interface->open_file(p.string(),
        platform::file_open_mode::read | platform::file_open_mode::binary);

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

    if (extension == "png")
    {
        return resource_encoding::image_png;
    }

    throw filesystem_provider_type_exception();
}

} // namespace resources
} // namespace aeon
