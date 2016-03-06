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

#include <gfx/gfx_resource_manager.h>
#include <resources/image.h>
#include <common/logger.h>
#include <build_config.h>

#ifdef AEON_PLATFORM_IOS
#include <OpenGLES/ES2/gl.h>
#else
#include <GLES2/gl2.h>
#endif // AEON_PLATFORM_IOS

namespace aeon
{
namespace gfx
{
namespace gles2
{

class texture_manager : public gfx::texture_manager
{
public:
    texture_manager();
    virtual ~texture_manager() = default;

private:
    texture_ptr __load(resources::image_ptr image) override;

    GLint __image_pixelformat_to_gl(resources::image::pixel_format format);

    aeon::logger::logger logger_;
};

} // namespace gles2
} // namespace gfx
} // namespace aeon
