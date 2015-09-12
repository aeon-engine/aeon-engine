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

#include <resources/filesystem_provider.h>
#include <boost/filesystem.hpp>
#include <aeon/streams.h>

namespace aeon
{
namespace resources
{

static boost::filesystem::path __get_real_path(boost::filesystem::path base, const std::string &path)
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

    if (!boost::filesystem::is_directory(p))
        throw filesystem_provider_list_exception();

    boost::filesystem::directory_iterator iterator(p);

    std::vector<resource_node> files;
    for (auto f : iterator)
    {
        resource_node_type type = resource_node_type::file;

        if (boost::filesystem::is_directory(f))
            type = resource_node_type::directory;

        // TODO: Verify this. Does this work work folders? Does this work at all?
        files.push_back(resource_node(f.path().filename().string(), type));
    }

    return std::move(files);
}

void filesystem_provider::read(const std::string &path, common::buffer_u8 &buffer)
{
    boost::filesystem::path p = __get_real_path(base_path_, path);
    aeon::streams::file_stream file(p);

    if (!file.good())
        throw filesystem_provider_read_exception();

    std::size_t size = file.size();

    if (size == 0)
        throw filesystem_provider_read_exception();

    common::buffer_u8 read_buffer;
    read_buffer.resize(size);

    size_t actual_size = file.read(read_buffer.data(), size);

    if (size != actual_size)
        throw filesystem_provider_read_exception();

    buffer = std::move(read_buffer);
}

resource_encoding filesystem_provider::get_encoding(const std::string &path) const
{
    std::string::size_type offset = path.find_last_of('.');

    if (offset == std::string::npos)
        throw filesystem_provider_type_exception();

    std::string extension = path.substr(offset);

    if (extension == "png")
    {
        return resource_encoding::image_png;
    }

    throw filesystem_provider_type_exception();
}

} // namespace resources
} // namespace aeon
