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

#include <gfx/gfx_texture_manager.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

class texture_manager : public gfx::texture_manager
{
public:
    texture_manager();
    ~texture_manager() override;

private:
    texture_ptr __load_texture(resources::image_ptr image) override;
};

} // namespace gl
} // namespace gfx
} // namespace aeon
