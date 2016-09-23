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

#include <gfx/gfx_texture.h>
#include <common/logger.h>

namespace aeon
{
namespace gfx
{
namespace null
{

class gfx_null_texture : public gfx::texture
{
    friend class gfx_null_texture_manager;

public:
    explicit gfx_null_texture(const resources::image &image);
    ~gfx_null_texture() override;

    void bind() const;

private:
    aeon::logger::logger logger_;
};

using gfx_null_texture_ptr = std::shared_ptr<gfx_null_texture>;

} // namespace null
} // namespace gfx
} // namespace aeon
