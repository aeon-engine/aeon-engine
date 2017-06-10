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

#include <managed_interface/assets/atlas.h>
#include <managed_interface/assets/material.h>
#include <managed_interface/mono_object_wrapper.h>
#include <managed_interface/core/types_conversion.h>
#include <aeon/mono/mono_jit.h>
#include <aeon/mono/mono_string.h>
#include <aeon/mono/mono_jit_manager.h>
#include <memory>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

void atlas::register_internal_calls()
{
    mono_jit::add_internal_call("AeonEngineMono.Assets.Atlas::.ctor(string)", &atlas::ctor);
    mono_jit::add_internal_call(
        "AeonEngineMono.Assets.Atlas::.ctor(AeonEngineMono.Assets.Material,AeonEngineMono.Types.Vector2f)",
        &atlas::ctor2);
    mono_jit::add_internal_call("AeonEngineMono.Assets.Atlas::GetRegionByIndex(int)", &atlas::get_region_by_index);
    mono_jit::add_internal_call("AeonEngineMono.Assets.Atlas::GetRegionByName(string)", &atlas::get_region_by_name);
}

auto atlas::get_atlas_from_mono_object(MonoObject *object) -> std::shared_ptr<gfx::atlas>
{
    return mono_object_wrapper<std::shared_ptr<gfx::atlas>>::get_native_object(object);
}

auto atlas::get_region_wrapper_from_mono_object(MonoObject *object) -> std::shared_ptr<atlas_region_wrapper>
{
    return mono_object_wrapper<std::shared_ptr<atlas_region_wrapper>>::get_native_object(object);
}

void atlas::ctor(MonoObject *this_ptr, MonoString *path)
{
    auto &asset_manager = mono_jit_manager::get_application().get_asset_manager();
    auto loaded_atlas = asset_manager.load_atlas(mono_string(path).str());

    mono_object_wrapper<std::shared_ptr<gfx::atlas>>::create(this_ptr, loaded_atlas);
}

void atlas::ctor2(MonoObject *this_ptr, MonoObject *material_ptr, vector2f size)
{
    auto material = material::get_material_from_mono_object(material_ptr);

    auto &asset_manager = mono_jit_manager::get_application().get_asset_manager();
    auto created_atlas = asset_manager.create_atlas(material, converter::convert(size));

    mono_object_wrapper<std::shared_ptr<gfx::atlas>>::create(this_ptr, created_atlas);
}

auto atlas::get_region_by_index(MonoObject *this_ptr, int index) -> MonoObject *
{
    auto atlas_ptr = get_atlas_from_mono_object(this_ptr);
    auto region = atlas_ptr->get_region_by_index(index);
    auto wrapper = std::make_shared<atlas_region_wrapper>(region, atlas_ptr);
    return mono_object_wrapper<std::shared_ptr<atlas_region_wrapper>>::create(wrapper);
}

auto atlas::get_region_by_name(MonoObject *this_ptr, MonoString *name) -> MonoObject *
{
    auto atlas_ptr = get_atlas_from_mono_object(this_ptr);
    auto region = atlas_ptr->get_region_by_name(mono_string(name).str());
    auto wrapper = std::make_shared<atlas_region_wrapper>(region, atlas_ptr);
    return mono_object_wrapper<std::shared_ptr<atlas_region_wrapper>>::create(wrapper);
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
