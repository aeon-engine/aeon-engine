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
#include <managed_interface/assets/atlas.h>
#include <managed_interface/mono_object_wrapper.h>
#include <aeon/mono/mono_jit.h>
#include <aeon/mono/mono_jit_manager.h>
#include <aeon/mono/mono_string.h>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

void sprite::register_internal_calls()
{
    mono_jit::add_internal_call("AeonEngineMono.Scene.Sprite::.ctor(AeonEngineMono.Assets.AtlasRegion,int,string)",
                                &sprite::ctor);
    mono_jit::add_internal_call("AeonEngineMono.Scene.Sprite::.ctor(AeonEngineMono.Assets.AtlasRegion,AeonEngineMono."
                                "Types.Vector2f,int,string)",
                                &sprite::ctor2);
}

void sprite::ctor(MonoObject *this_ptr, MonoObject *region, int z_order, MonoString *name)
{
    auto &scene_manager = mono_jit_manager::get_application().get_scene_manager();
    auto region_wrapper = atlas::get_region_wrapper_from_mono_object(region);
    auto sprite = scene_manager.create_component<scene::sprite>(region_wrapper->atlas, region_wrapper->region, z_order,
                                                                mono_string(name).str());

    mono_object_wrapper<std::shared_ptr<scene::component>>::create(this_ptr, sprite);
}

void sprite::ctor2(MonoObject *this_ptr, MonoObject *region, vector2f size, int z_order, MonoString *name)
{
    auto &scene_manager = mono_jit_manager::get_application().get_scene_manager();
    auto region_wrapper = atlas::get_region_wrapper_from_mono_object(region);
    auto sprite = scene_manager.create_component<scene::sprite>(
        region_wrapper->atlas, region_wrapper->region, glm::vec2{size.x, size.y}, z_order, mono_string(name).str());

    mono_object_wrapper<std::shared_ptr<scene::component>>::create(this_ptr, sprite);
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
