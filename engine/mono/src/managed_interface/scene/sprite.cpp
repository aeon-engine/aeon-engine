/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <managed_interface/scene/sprite.h>
#include <managed_interface/mono_object_wrapper.h>
#include <aeon/mono/mono_jit.h>
#include <aeon/mono/mono_jit_manager.h>
#include <aeon/mono/mono_string.h>
#include <aeon/scene/components/sprite.h>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

void sprite::register_internal_calls()
{
    mono_jit::add_internal_call("AeonEngineMono.Scene.Sprite::.ctor(AeonEngineMono.Assets.AtlasRegion,int,string)",
                                aeon_mono_auto_wrap(sprite::ctor));
    mono_jit::add_internal_call("AeonEngineMono.Scene.Sprite::.ctor(AeonEngineMono.Assets.AtlasRegion,AeonEngineMono."
                                "Types.Vector2f,int,string)",
                                aeon_mono_auto_wrap(sprite::ctor2));
}

void sprite::ctor(MonoObject *this_ptr, std::shared_ptr<managed_interface::atlas_region_wrapper> region, int z_order,
                  std::string name)
{
    auto &scene_manager = mono_jit_manager::get_application().get_scene_manager();
    auto sprite = scene_manager.create_component<scene::sprite>(region->atlas, region->region, z_order, name);

    mono_object_wrapper<std::shared_ptr<scene::component>>::create(this_ptr, sprite);
}

void sprite::ctor2(MonoObject *this_ptr, std::shared_ptr<managed_interface::atlas_region_wrapper> region,
                   glm::vec2 size, int z_order, std::string name)
{
    auto &scene_manager = mono_jit_manager::get_application().get_scene_manager();
    auto sprite = scene_manager.create_component<scene::sprite>(region->atlas, region->region, size, z_order, name);

    mono_object_wrapper<std::shared_ptr<scene::component>>::create(this_ptr, sprite);
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
