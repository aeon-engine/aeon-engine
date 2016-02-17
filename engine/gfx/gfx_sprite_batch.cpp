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

#include <gfx/gfx_sprite_batch.h>

namespace aeon
{
namespace gfx
{

sprite_batch::sprite_batch(material_ptr material, std::uint16_t sprites_per_buffer)
    : material_(material)
    , sprites_per_buffer_(sprites_per_buffer)
{
}

} // namespace gfx
} // namespace aeon
