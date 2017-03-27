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

#include <aeon/io/io_filesystem_interface.h>
#include <aeon/resources/providers/filesystem_provider.h>
#include <aeon/resources/resource_manager.h>
#include <aeon/io/io_interface.h>

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

auto filesystem_provider::exists(const std::string &path) const -> bool
{
    auto &io = __get_resource_manager()->get_io_interface();
    auto &filesystem_interface = io.get_filesystem_interface();
    return filesystem_interface.exists(__get_real_path(base_path_, path));
}

auto filesystem_provider::list(const std::string & /*path*/) const -> std::vector<resource_node>
{
    AEON_LOG_ERROR(logger_) << "List method is not implemented yet." << std::endl;
    throw std::runtime_error("Not yet implemented.");
}

void filesystem_provider::read(const std::string &path, std::vector<std::uint8_t> &buffer)
{
    AEON_LOG_TRACE(logger_) << "Read file at '" << path << "'." << std::endl;

    auto real_path = __get_real_path(base_path_, path);

    auto &io = __get_resource_manager()->get_io_interface();
    auto &filesystem_interface = io.get_filesystem_interface();

    if (!filesystem_interface.exists(real_path))
    {
        AEON_LOG_ERROR(logger_) << "Could not read file at '" << path << "'. File does not exist." << std::endl;
        throw filesystem_provider_read_exception();
    }

    auto file = filesystem_interface.open_file(real_path, io::file_open_mode::read | io::file_open_mode::binary);

    auto read_buffer = std::vector<std::uint8_t>();
    file->read(read_buffer);
    buffer = std::move(read_buffer);
}

auto filesystem_provider::get_encoding(const std::string &path) const -> resource_encoding
{
    auto offset = path.find_last_of('.');

    if (offset == std::string::npos)
    {
        AEON_LOG_ERROR(logger_) << "Could not determine resource encoding from file extension." << std::endl;
        throw filesystem_provider_type_exception();
    }

    auto extension = path.substr(offset + 1);

    if (extension == "amf")
        return resource_encoding::material;
    if (extension == "asc")
        return resource_encoding::scene;
    if (extension == "prg")
        return resource_encoding::shader;
    if (extension == "ata")
        return resource_encoding::atlas;
    if (extension == "png")
        return resource_encoding::image_png;
    if (extension == "dds")
        return resource_encoding::image_dds;
    if (extension == "3ds" || extension == "ase" || extension == "dae")
        // Assimp supports more formats, but these should be the most common ones. More extensions could be added later.
        return resource_encoding::mesh_assimp;

    AEON_LOG_ERROR(logger_) << "Unknown or unsupported file extension: '" << extension << "'." << std::endl;
    throw filesystem_provider_type_exception();
}

} // namespace resources
} // namespace aeon
