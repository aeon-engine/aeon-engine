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
    mono_jit::add_internal_call("AeonEngineMono.Assets.Atlas::.ctor(string)", aeon_mono_auto_wrap(atlas::ctor));
    mono_jit::add_internal_call(
        "AeonEngineMono.Assets.Atlas::.ctor(AeonEngineMono.Assets.Material,AeonEngineMono.Types.Vector2f)",
        aeon_mono_auto_wrap(atlas::ctor2));
    mono_jit::add_internal_call("AeonEngineMono.Assets.Atlas::GetRegionByIndex(int)",
                                aeon_mono_auto_wrap(atlas::get_region_by_index));
    mono_jit::add_internal_call("AeonEngineMono.Assets.Atlas::GetRegionByName(string)",
                                aeon_mono_auto_wrap(atlas::get_region_by_name));
}

void atlas::ctor(MonoObject *this_ptr, std::string path)
{
    auto &asset_manager = mono_jit_manager::get_application().get_asset_manager();
    auto loaded_atlas = asset_manager.load_atlas(path);

    mono_object_wrapper<std::shared_ptr<gfx::atlas>>::create(this_ptr, loaded_atlas);
}

void atlas::ctor2(MonoObject *this_ptr, std::shared_ptr<gfx::material> material, glm::vec2 size)
{
    auto &asset_manager = mono_jit_manager::get_application().get_asset_manager();
    auto created_atlas = asset_manager.create_atlas(material, size);

    mono_object_wrapper<std::shared_ptr<gfx::atlas>>::create(this_ptr, created_atlas);
}

auto atlas::get_region_by_index(std::shared_ptr<gfx::atlas> this_ptr, int index)
    -> std::shared_ptr<managed_interface::atlas_region_wrapper>
{
    auto region = this_ptr->get_region_by_index(index);
    return std::make_shared<atlas_region_wrapper>(region, this_ptr);
}

auto atlas::get_region_by_name(std::shared_ptr<gfx::atlas> this_ptr, std::string name)
    -> std::shared_ptr<managed_interface::atlas_region_wrapper>
{
    auto region = this_ptr->get_region_by_name(name);
    return std::make_shared<atlas_region_wrapper>(region, this_ptr);
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
