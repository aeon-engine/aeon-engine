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

#include <resources/resource.h>
#include <resources/exceptions.h>
#include <gfx/gfx_material.h>
#include <resources/wrappers/font_resource_wrapper.h>
#include <common/buffer.h>
#include <common/logger.h>
#include <vector>
#include <memory>

namespace aeon
{
namespace resources
{

class font_glyph
{
public:
    explicit font_glyph(float top_, float left_, float width_, float height_, float advance_x_)
        : top(top_)
        , left(left_)
        , width(width_)
        , height(height_)
        , advance_x(advance_x_)
    {
    }

    ~font_glyph() = default;

    float top;
    float left;

    float width;
    float height;

    float advance_x;
};

using font_glyphs = std::vector<font_glyph>;

class font : public resource
{
public:
    explicit font(resource_wrapper_ptr wrapper, const font_glyphs &glyphs);
    virtual ~font();

    gfx::material_ptr get_material() const;

private:
    aeon::logger::logger logger_;
    gfx::material_ptr material_;
    font_glyphs glyphs_;
};

using font_ptr = std::shared_ptr<font>;

} // namespace resources
} // namespace aeon
