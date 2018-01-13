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

#pragma once

#include <aeon/gfx/gfx_device.h>
#include <aeon/input/input_handler.h>
#include <aeon/common/exception.h>
#include <vector>
#include <memory>

namespace aeon
{
namespace platform
{

DEFINE_EXCEPTION_OBJECT(platform_exception, aeon::common::exception, "Platform exception.");

class monitor;
class window;
class window_settings;

class platform_manager
{
public:
    explicit platform_manager(input::input_handler &input_handler, gfx::device &device);
    virtual ~platform_manager();

    /*!
     * Enter the engine's main loop. You must first call initialize before calling run.
     * This function will not return until stop() is called.
     */
    virtual void run() = 0;

    /*!
     * Stop the mainloop. Has no effect if run hasn't been called.
     */
    virtual void stop() = 0;

    /*!
     * Get a list of all monitors connected to this system.
     */
    virtual auto get_monitors() -> std::vector<monitor *> = 0;

    /*!
     * Create a window. A window can be created on a specific monitor. When no monitor is
     * given, the window appears on the main monitor.
     */
    virtual auto create_window(const window_settings &settings, monitor *monitor = nullptr) -> window * = 0;

    /*!
     * Get the associated input handler.
     */
    auto get_input_handler() const -> input::input_handler &;

    /*!
     * Get the associated graphics device.
     */
    auto get_device() const -> gfx::device &;

private:
    input::input_handler &input_handler_;
    gfx::device &device_;
};

} // namespace platform
} // namespace aeon
