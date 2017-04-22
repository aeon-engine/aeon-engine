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

#include <aeon/platform/platform_manager.h>
#include <aeon/platform/glfw/glfw_platform_monitor.h>
#include <aeon/logger/logger.h>

namespace aeon
{
namespace platform
{
namespace glfw
{

class glfw_platform_manager : public platform_manager
{
public:
    explicit glfw_platform_manager(input::input_handler &input_handler, gfx::device &device);
    virtual ~glfw_platform_manager();

    void run() override;

    void stop() override;

    auto get_monitors() -> std::vector<monitor *> override;

    auto create_window(const window_settings &settings, monitor *monitor = nullptr) -> std::shared_ptr<window> override;

private:
    void __initialize_glfw() const;

    logger::logger logger_;
    bool initialized_;

    std::vector<std::unique_ptr<glfw_monitor>> monitors_;
    bool running_;
    double previous_time_;
};

} // namespace glfw
} // namespace platform
} // namespace aeon
