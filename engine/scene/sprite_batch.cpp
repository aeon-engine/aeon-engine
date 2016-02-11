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

#include <scene/sprite_batch.h>

namespace aeon
{
namespace scene
{

sprite_batch::sprite_batch(scene_manager *scene_manager)
    : scene_object(render_layer::overlay, scene_object_type::renderable, scene_manager)
{
}

} // namespace scene
} // namespace aeon
