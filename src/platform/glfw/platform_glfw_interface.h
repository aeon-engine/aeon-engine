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

#pragma once

#include <memory>
#include <platform/platform_interface.h>
#include <platform/glfw/platform_glfw_window.h>

namespace aeon
{
namespace platform
{
namespace glfw
{

class platform_interface : public platform::platform_interface
{
public:
    using windows = std::vector<platform_window_ptr>;

    platform_interface();
    virtual ~platform_interface() override;

    void initialize() override;

    void run() override;
    void stop() override;

    platform_monitors get_monitors() override;

    platform::platform_window_ptr create_window(int width, int height, const std::string &name,
        platform_monitor_ptr monitor = nullptr) override;

private:
    windows windows_;

    bool initialized_;
    bool running_;
};

} // namespace glfw
} // namespace platform
} // namespace aeon
