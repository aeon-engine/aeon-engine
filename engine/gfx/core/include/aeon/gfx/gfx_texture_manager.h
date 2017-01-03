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

#include <aeon/data/image.h>
#include <aeon/gfx/gfx_texture.h>

#include <memory>

namespace aeon
{
namespace gfx
{

class texture_manager
{
public:
    texture_manager() = default;
    virtual ~texture_manager() = default;

    virtual std::shared_ptr<texture> create(const data::image &image_data) = 0;
};

} // namespace gfx
} // namespace aeon
