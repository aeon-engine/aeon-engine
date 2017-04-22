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

#include <aeon/resources/wrappers/image_resource_wrapper.h>
#include <aeon/resources/wrappers/material_resource_wrapper.h>
#include <aeon/resources/providers/resource_provider.h>
#include <aeon/resources/exceptions.h>
#include <aeon/resources/codecs/codec_manager.h>
#include <aeon/resources/wrappers/resource_wrapper.h>
#include <aeon/resources/codecs/codec_manager.h>
#include <aeon/io/io_interface.h>
#include <aeon/resources/wrappers/atlas_resource_wrapper.h>
#include <aeon/resources/wrappers/mesh_resource_wrapper.h>
#include <aeon/resources/atlas.h>
#include <aeon/common/logger.h>
#include <map>

namespace aeon
{
namespace resources
{

DEFINE_EXCEPTION_OBJECT(resource_manager_exception, resource_exception, "Generic resource manager exception.");

DEFINE_EXCEPTION_OBJECT(resource_manager_mount_exception, resource_manager_exception,
                        "Could not mount resource provider.");

DEFINE_EXCEPTION_OBJECT(resource_manager_duplicate_mount_exception, resource_manager_mount_exception,
                        "Could not mount resource provider. Duplicate mountpoint given.");

class resource_manager
{
    using mount_points = std::map<std::string, std::shared_ptr<resource_provider>>;

public:
    explicit resource_manager(io::io_interface &io);
    ~resource_manager();

    void mount(const std::shared_ptr<resource_provider> &provider, const std::string &mountpoint = "/");
    void unmount(const std::string &mountpoint);

    template <typename T>
    auto load_resource_wrapper(const std::string &path)
    {
        AEON_LOG_DEBUG(logger_) << "Loading resource wrapper '" << path << "'." << std::endl;

        auto real_path = std::string();
        auto best_match_provider = __find_best_match_provider(path, real_path);

        if (!best_match_provider)
            return std::shared_ptr<T>();

        return std::make_shared<T>(*this, real_path, best_match_provider);
    }

    auto &get_io_interface()
    {
        return io_;
    }

    auto &get_codec_manager()
    {
        return codec_manager_;
    }

private:
    auto __find_best_match_provider(const std::string &path, std::string &provider_path) const
        -> std::shared_ptr<resource_provider>;

    aeon::logger::logger logger_;
    io::io_interface &io_;
    mount_points mount_points_;
    codec_manager codec_manager_;
};

} // namespace resources
} // namespace aeon
