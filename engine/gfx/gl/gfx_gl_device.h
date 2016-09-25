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

#include <gfx/gfx_device.h>
#include <aeon/common/exception.h>
#include <aeon/common/logger.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

DEFINE_EXCEPTION_OBJECT(gl_initialized_exception, aeon::common::exception, "OpenGL Device already initialized.");
DEFINE_EXCEPTION_OBJECT(gl_device_exception, aeon::common::exception, "OpenGL Device Exception");

class gfx_gl_device : public gfx::device
{
public:
    gfx_gl_device();
    virtual ~gfx_gl_device() = default;

    void __initialize_impl() override;

    void set_clear_color(const common::types::color &c) override;
    void set_viewport(scene::viewport *vp) override;

    void clear_buffer(int buffer_flag) override;

    mesh_ptr create_mesh(material_ptr material) override;

private:
    void __create_managers();
    void __setup_opengl() const;

    aeon::logger::logger logger_;
};

} // namespace gl
} // namespace gfx
} // namespace aeon
