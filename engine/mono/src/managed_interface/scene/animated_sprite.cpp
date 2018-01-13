/*
 * Copyright (c) 2012-2018 Robin Degen
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
                                aeon_mono_auto_wrap(animated_sprite::ctor));
    mono_jit::add_internal_call("AeonEngineMono.Scene.AnimatedSprite::Run", aeon_mono_auto_wrap(animated_sprite::run));
    mono_jit::add_internal_call("AeonEngineMono.Scene.AnimatedSprite::Stop",
                                aeon_mono_auto_wrap(animated_sprite::stop));
    mono_jit::add_internal_call("AeonEngineMono.Scene.AnimatedSprite::set_AnimationSequence(int)",
                                aeon_mono_auto_wrap(animated_sprite::set_animation_sequence));
}

void animated_sprite::ctor(MonoObject *this_ptr, std::shared_ptr<gfx::atlas> atlas, int z_order,
                           std::shared_ptr<scene::sprite_animation_settings> settings, std::string name)
{
    auto &scene_manager = mono_jit_manager::get_application().get_scene_manager();
    auto sprite = scene_manager.create_component<scene::animated_sprite>(atlas, z_order, *settings, name);

    mono_object_wrapper<std::shared_ptr<scene::component>>::create(this_ptr, sprite);
}

void animated_sprite::run(std::shared_ptr<scene::animated_sprite> this_ptr)
{
    this_ptr->run();
}

void animated_sprite::stop(std::shared_ptr<scene::animated_sprite> this_ptr)
{
    this_ptr->stop();
}

void animated_sprite::set_animation_sequence(std::shared_ptr<scene::animated_sprite> this_ptr, int index)
{
    this_ptr->set_animation_sequence(index);
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
