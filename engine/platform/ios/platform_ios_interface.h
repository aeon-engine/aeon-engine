/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
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
#include <common/logger.h>
#include <gfx/gfx_render_target.h>
#include <platform/platform_interface.h>
#include <platform/ios/platform_ios_window.h>

namespace aeon
{
namespace platform
{
namespace ios
{

class platform_interface : public platform::platform_interface
{
public:
    using render_targets = std::vector<gfx::render_target_ptr>;

    platform_interface(gfx::device &device);
    virtual ~platform_interface() override;

    void initialize(const application_settings &settings) override;

    int run(int argc, char *argv[], const application_settings &settings, std::function<void()> callback) override;
    void stop() override;
    
    void init_rest();

    platform_monitors get_monitors() override;

    platform::platform_window_ptr create_window(int width, int height, const std::string &name,
                                                platform_monitor_ptr monitor = nullptr) override;

    platform::platform_window_ptr get_default_window() override;

    void render_frame();

    static platform_interface *singleton;

private:
    aeon::logger::logger logger_;

    render_targets render_targets_;
    platform::platform_window_ptr main_window_;
    std::function<void()> callback_;
    bool initialized_;
    bool running_;
    double previous_time_;
};

} // namespace ios
} // namespace platform
} // namespace aeon
