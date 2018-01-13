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

#pragma once

#include <aeon/mono/mono_type_conversion.h>
#include <managed_interface/mono_object_wrapper.h>
#include <mono/metadata/object.h>
#include <aeon/gfx/gfx_shader.h>
#include <memory>

namespace aeon
{
namespace mono
{

register_basic_mono_converter_for_wrapper(std::shared_ptr<gfx::shader>);

namespace managed_interface
{

class shader
{
public:
    static void register_internal_calls();

    static auto get_shader_from_mono_object(MonoObject *object) -> std::shared_ptr<gfx::shader>;

private:
    static void ctor(MonoObject *this_ptr, std::string path);
};

} // namespace managed_interface
} // namespace mono
} // namespace aeon
