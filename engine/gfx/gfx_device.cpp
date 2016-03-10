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

#include <gfx/gfx_device.h>

namespace aeon
{
namespace gfx
{

device::device()
    : initialized_(false)
{
}

void device::initialize()
{
    __initialize_impl();

    set_clear_color(common::types::color(1.0f, 0.0f, 0.0f));
}

} // namespace gfx
} // namespace aeon
