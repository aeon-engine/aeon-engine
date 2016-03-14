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

#include <resources/font.h>

namespace aeon
{
namespace resources
{

font::font(resource_wrapper_ptr wrapper, const font_glyphs &glyphs)
    : resource(wrapper)
    , logger_(common::logger::get_singleton(), "Resources::Font")
    , material_(nullptr)
    , glyphs_(glyphs)
{
    AEON_LOG_TRACE(logger_) << "Created font resource." << std::endl;
}

font::~font()
{
    AEON_LOG_TRACE(logger_) << "Deleted font resource." << std::endl;
}

gfx::material_ptr font::get_material() const
{
    return material_;
}

} // namespace resources
} // namespace aeon
