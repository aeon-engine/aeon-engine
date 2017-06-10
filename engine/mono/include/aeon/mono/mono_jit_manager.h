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

#pragma once

#include <aeon/application/desktop_application.h>
#include <aeon/mono/mono_jit.h>
#include <aeon/mono/mono_assembly.h>
#include <aeon/mono/mono_class_instance.h>
#include <aeon/mono/mono_method.h>
#include <aeon/mono/mono_method_thunk.h>
#include <aeon/logger/logger.h>
#include <aeon/common/noncopyable.h>

namespace aeon
{
namespace mono
{

class mono_jit_manager : public common::noncopyable
{
public:
    mono_jit_manager(application::desktop_application &application);
    virtual ~mono_jit_manager();

    void load_assembly(const std::string &path);

    void call_initialize();
    auto call_update(float dt) -> bool;

    static auto get_application() -> application::desktop_application &;

    static mono_assembly main_assembly;
    static mono_assembly engine_assembly;

private:
    void initialize_jit() const;

    logger::logger logger_;
    mono_jit jit_;
    mono_class_instance main_class_instance_;
    mono_method_thunk<void()> initialize_method_;
    mono_method_thunk<bool(float)> update_method_;

    static application::desktop_application *application_;
};

} // namespace mono
} // namespace aeon
