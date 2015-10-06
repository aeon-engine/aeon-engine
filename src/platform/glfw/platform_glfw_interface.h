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

namespace aeon
{
namespace platform
{
namespace glfw
{

class platform_interface : public platform::platform_interface
{
public:
    platform_interface();
    virtual ~platform_interface() override;

    void initialize() override;

    void run() override;
    void stop() override;

    platform_monitors get_monitors() override;

    platform_window_ptr create_window(int width, int height, const std::string &name,
        platform_monitor_ptr monitor = nullptr) override;

private:
    bool initialized_;
    bool running_;
};

} // namespace glfw
} // namespace platform
} // namespace aeon
