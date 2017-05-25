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

#include <aeon/application/base_application.h>

namespace aeon
{
namespace application
{

base_application::base_application(context context)
    : logger_backend_(std::move(context.logger_backend))
    , logger_(common::logger::get_singleton(), "Application")
    , config_file_(std::move(context.config_file))
    , io_(std::move(context.io_interface))
    , input_handler_(std::move(context.input_handler))
    , device_(std::move(context.device))
    , platform_(std::move(context.platform_manager))
    , resource_manager_(std::move(context.resource_manager))
    , scene_manager_(std::move(context.scene_manager))
    , codec_manager_(std::move(context.codec_manager))
    , asset_manager_(std::move(context.asset_manager))
{
    AEON_LOG_MESSAGE(logger_) << "Aeon Engine (" << buildinfo::full_version << ", " << buildinfo::build_date << ")."
                              << std::endl;
}

base_application::~base_application() = default;

} // namespace application
} // namespace aeon
