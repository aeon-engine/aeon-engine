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

#include <aeon/application/desktop_application.h>
#include <aeon/platform/platform_window_settings.h>
#include <aeon/ptree/config_file.h>
#include <build_config.h>

namespace aeon::application
{

desktop_application::desktop_application(context context)
    : base_application(std::move(context))
    , window_(nullptr)
{
    device_->initialize();
    __create_window();
}

desktop_application::~desktop_application() = default;

auto desktop_application::get_main_window() const -> platform::window &
{
    return *window_;
}

void desktop_application::__create_window()
{
    ptree::config_file config{*config_file_};

    const auto width = config.get<int>("engine", "window_width", AEON_DEFAULT_WINDOW_WIDTH);
    const auto height = config.get<int>("engine", "window_height", AEON_DEFAULT_WINDOW_HEIGHT);
    const auto title = config.get<std::string>("engine", "window_title", AEON_DEFAULT_WINDOW_TITLE);
    const auto multisample = config.get<int>("engine", "multisample", 0);
    const auto double_buffer = config.get<bool>("engine", "double_buffer", true);

    auto settings = platform::window_settings{width, height, title};
    settings.set_multisample(multisample);
    settings.set_buffer_mode(double_buffer ? platform::buffer_mode::double_buffer
                                           : platform::buffer_mode::single_buffer);

    window_ = platform_->create_window(settings);
}
} // namespace aeon::application
