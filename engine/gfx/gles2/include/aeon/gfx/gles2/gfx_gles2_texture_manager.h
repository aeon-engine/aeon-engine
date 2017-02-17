/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#include <aeon/gfx/gfx_texture_manager.h>
#include <aeon/common/logger.h>
#include <GLES2/gl2.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

class gfx_gles2_texture_manager : public gfx::texture_manager
{
public:
    gfx_gles2_texture_manager();
    virtual ~gfx_gles2_texture_manager() = default;

private:
    std::shared_ptr<texture> create(const data::image &image_data) override;

    GLint __image_pixelformat_to_gl(data::image::pixel_format format) const;

    aeon::logger::logger logger_;
};

} // namespace gles2
} // namespace gfx
} // namespace aeon
