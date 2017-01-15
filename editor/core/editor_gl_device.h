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
#include <aeon/gfx/gl/gfx_gl_device.h>

namespace aeon
{
namespace editor
{

class editor_gl_device : public gfx::gl::gfx_gl_device
{
public:
    editor_gl_device(platform::platform_interface &platform, input::input_handler &input_handler);
    virtual ~editor_gl_device() override;

    void initialize_editor();

};

} // namespace editor
} // namespace aeon
