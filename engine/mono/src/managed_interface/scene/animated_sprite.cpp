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

#include <managed_interface/scene/animated_sprite.h>
#include <managed_interface/assets/atlas.h>
#include <managed_interface/scene/animated_sprite_settings.h>
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

void animated_sprite::register_internal_calls()
{
    mono_jit::add_internal_call("AeonEngineMono.Scene.AnimatedSprite::.ctor(AeonEngineMono.Assets.Atlas,int,"
                                "AeonEngineMono.Scene.SpriteAnimationSettings,string)",
                                &animated_sprite::ctor);
    mono_jit::add_internal_call("AeonEngineMono.Scene.AnimatedSprite::Run", &animated_sprite::run);
    mono_jit::add_internal_call("AeonEngineMono.Scene.AnimatedSprite::Stop", &animated_sprite::stop);
    mono_jit::add_internal_call("AeonEngineMono.Scene.AnimatedSprite::set_AnimationSequence(int)",
                                &animated_sprite::set_animation_sequence);
}

auto animated_sprite::get_animated_sprite_from_mono_object(MonoObject *object)
    -> std::shared_ptr<scene::animated_sprite>
{
    auto component = mono_object_wrapper<std::shared_ptr<scene::component>>::get_native_object(object);
    return std::dynamic_pointer_cast<scene::animated_sprite>(component);
}

void animated_sprite::ctor(MonoObject *this_ptr, MonoObject *atlas, int z_order, MonoObject *settings, MonoString *name)
{
    auto &scene_manager = mono_jit_manager::get_application().get_scene_manager();
    auto atlas_obj = atlas::get_atlas_from_mono_object(atlas);
    auto &settings_obj = animated_sprite_settings::get_animated_sprite_settings_from_mono_object(settings);
    auto sprite = scene_manager.create_component<scene::animated_sprite>(atlas_obj, z_order, settings_obj,
                                                                         mono_string(name).str());

    mono_object_wrapper<std::shared_ptr<scene::component>>::create(this_ptr, sprite);
}

void animated_sprite::run(MonoObject *this_ptr)
{
    auto sprite = get_animated_sprite_from_mono_object(this_ptr);
    sprite->run();
}

void animated_sprite::stop(MonoObject *this_ptr)
{
    auto sprite = get_animated_sprite_from_mono_object(this_ptr);
    sprite->stop();
}

void animated_sprite::set_animation_sequence(MonoObject *this_ptr, int index)
{
    auto sprite = get_animated_sprite_from_mono_object(this_ptr);
    sprite->set_animation_sequence(index);
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
