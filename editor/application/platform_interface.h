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

#include <aeon/common/logger.h>
#include <gfx/gfx_render_target.h>
#include <platform/platform_interface.h>

namespace aeon
{
namespace editor
{

class platform_interface : public platform::platform_interface
{
public:
    using render_targets = std::vector<gfx::render_target_ptr>;

    platform_interface(int argc, char *argv[]);
    virtual ~platform_interface() override;

    void initialize() override;

    void run() override;
    void stop() override;

    platform::platform_monitors get_monitors() override;

    platform::platform_window_ptr create_window(const platform::platform_window_settings &settings,
        platform::platform_monitor_ptr monitor = nullptr) override;

private:
    aeon::logger::logger logger_;
    render_targets render_targets_;

    bool initialized_;
};

} // namespace editor
} // namespace aeon