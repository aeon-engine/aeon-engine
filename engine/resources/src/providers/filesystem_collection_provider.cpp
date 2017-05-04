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
#include <aeon/resources/providers/filesystem_collection_provider.h>
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

filesystem_collection_provider::filesystem_collection_provider(io::io_interface &io_interface,
                                                               const std::string &base_path)
    : resource_collection_provider()
    , logger_(common::logger::get_singleton(), "Resources::FilesystemCollectionProvider")
    , base_path_(base_path)
    , io_interface_(io_interface)
{
    AEON_LOG_TRACE(logger_) << "Created Filesystem Collection Provider for base path: '" << base_path << "'."
                            << std::endl;
}

filesystem_collection_provider::~filesystem_collection_provider()
{
    AEON_LOG_TRACE(logger_) << "Deleted Filesystem Collection Provider for base path: '" << base_path_ << "'."
                            << std::endl;
}

auto filesystem_collection_provider::exists(const std::string &path) const -> bool
{
    auto &filesystem_interface = io_interface_.get_filesystem_interface();
    return filesystem_interface.exists(__get_real_path(base_path_, path));
}

auto filesystem_collection_provider::list(const std::string & /*path*/) const -> std::vector<resource_info>
{
    AEON_LOG_ERROR(logger_) << "List method is not implemented yet." << std::endl;
    throw std::runtime_error("Not yet implemented.");
}

auto filesystem_collection_provider::get_info(const std::string &path) const -> resource_info
{
    // TODO: This method is only partially implemented for the encoding.
    auto offset = path.find_last_of('.');

    if (offset == std::string::npos)
    {
        AEON_LOG_ERROR(logger_) << "Could not determine resource encoding from file extension." << std::endl;
        throw filesystem_collection_provider_type_exception();
    }

    auto extension = path.substr(offset + 1);

    return resource_info(path, resource_type::data, resource_encoding(extension));
}

auto filesystem_collection_provider::open(const std::string &path) const -> std::unique_ptr<resource_provider>
{
    AEON_LOG_TRACE(logger_) << "Read file at '" << path << "'." << std::endl;

    auto real_path = __get_real_path(base_path_, path);

    auto &filesystem_interface = io_interface_.get_filesystem_interface();

    if (!filesystem_interface.exists(real_path))
    {
        AEON_LOG_ERROR(logger_) << "Could not read file at '" << path << "'. File does not exist." << std::endl;
        throw filesystem_collection_provider_read_exception();
    }

    auto file = filesystem_interface.open_file(real_path, io::file_open_mode::read | io::file_open_mode::binary);
    auto resource_info = get_info(path);
    return std::make_unique<filesystem_provider>(resource_info, std::move(file));
}

} // namespace resources
} // namespace aeon
