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

#include <aeon/gfx/gfx_imgui_listener.h>
#include <aeon/utility.h>

namespace aeon
{
namespace gfx
{

class imgui_renderer : public utility::listener_subject<imgui_listener>
{
public:
    imgui_renderer() = default;
    virtual ~imgui_renderer() = default;
};

} // namespace gfx
} // namespace aeon
