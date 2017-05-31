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

#include <aeon/mono/mono_jit_manager.h>
#include <aeon/mono/mono_class.h>
#include <aeon/mono/mono_class_instance.h>
#include <aeon/mono/mono_method.h>
#include <aeon/common/logger.h>

#include <managed_interface/core/object.h>
#include <managed_interface/gfx/viewport.h>
#include <managed_interface/resources/filesystem_collection_provider.h>
#include <managed_interface/resources/resource_manager.h>
#include <managed_interface/scene/orthographic_camera.h>
#include <managed_interface/scene/perspective_camera.h>
#include <managed_interface/scene/sprite.h>

#include <cassert>

namespace aeon
{
namespace mono
{

application::desktop_application *mono_jit_manager::application_ = nullptr;

mono_jit_manager::mono_jit_manager(application::desktop_application &application)
    : logger_(common::logger::get_singleton(), "Mono::JitManager")
    , jit_("AeonEngine")
    , assembly_()
    , engine_assembly_()
{
    application_ = &application;
    initialize_jit();
}

mono_jit_manager::~mono_jit_manager() = default;

void mono_jit_manager::load_assembly(const std::string &path)
{
    AEON_LOG_DEBUG(logger_) << "Loading mono assembly " << path << std::endl;
    assert(!assembly_.get_mono_assembly_ptr());
    assembly_ = jit_.load_assembly(path);
    engine_assembly_ = jit_.load_assembly("AeonEngineMono.dll");

    managed_interface::object::initialize_class_field(engine_assembly_);
}

int mono_jit_manager::main() const
{
    AEON_LOG_DEBUG(logger_) << "Calling MonoApplication.Initialize." << std::endl;

    auto mono_class = assembly_.get_class("MonoApplication");
    auto mono_class_instance = assembly_.new_class_instance(mono_class);

    // TODO: Fix the return value of mono methods.
    auto method = mono_class_instance.get_method("Initialize");
    method();

    return 0;
}

auto mono_jit_manager::get_application() -> application::desktop_application &
{
    return *application_;
}

void mono_jit_manager::initialize_jit() const
{
    managed_interface::filesystem_collection_provider::register_internal_calls();
    managed_interface::viewport::register_internal_calls();
    managed_interface::object::register_internal_calls();
    managed_interface::resource_manager::register_internal_calls();
    managed_interface::orthographic_camera::register_internal_calls();
    managed_interface::perspective_camera::register_internal_calls();
    managed_interface::sprite::register_internal_calls();
}

} // namespace mono
} // namespace aeon
