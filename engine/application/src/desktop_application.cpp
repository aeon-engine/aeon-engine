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

namespace aeon
{
namespace application
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
    const auto width = config_file_->get<int>("window_width", AEON_DEFAULT_WINDOW_WIDTH);
    const auto height = config_file_->get<int>("window_height", AEON_DEFAULT_WINDOW_HEIGHT);
    const auto title = config_file_->get<std::string>("window_title", AEON_DEFAULT_WINDOW_TITLE);
    const auto multisample = config_file_->get<int>("multisample", 0);
    const auto double_buffer = config_file_->get<bool>("double_buffer", true);

    auto settings = platform::window_settings{width, height, title};
    settings.set_multisample(multisample);
    settings.set_buffer_mode(double_buffer ? platform::buffer_mode::double_buffer
                                           : platform::buffer_mode::single_buffer);

    window_ = platform_->create_window(settings);
}

} // namespace application
} // namespace aeon
