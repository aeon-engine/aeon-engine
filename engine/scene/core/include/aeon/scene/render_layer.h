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

namespace aeon
{
namespace scene
{

struct render_layer
{
    enum render_layer_enum
    {
        special = 0, // Special layer used for non renderable objects like camera's and sound.
        overlay = 10,
        world_geometry = 50,
        sky = 100,
        max = 255 // The highest render layer group.
    };
};

} // namespace scene
} // namespace aeon
