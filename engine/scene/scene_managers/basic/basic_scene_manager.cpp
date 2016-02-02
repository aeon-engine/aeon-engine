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

#include <scene/scene_managers/basic/basic_scene_manager.h>

namespace aeon
{
namespace scene
{

basic_scene_manager::basic_scene_manager(gfx::device &device)
    : scene_manager(device)
{
}

basic_scene_manager::~basic_scene_manager()
{
}

void basic_scene_manager::__prepare_render_queue(camera* cam)
{
    queue_.clear_render_objects();
}

} // namespace scene
} // namespace aeon
