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

#include <managed_interface/core/types.h>
#include <mono/metadata/object.h>
#include <aeon/gfx/gfx_atlas.h>
#include <memory>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

class atlas_region_wrapper : common::noncopyable
{
public:
    explicit atlas_region_wrapper(const data::atlas::region &region, std::shared_ptr<gfx::atlas> atlas)
        : region(region)
        , atlas(atlas)
    {
    }

    ~atlas_region_wrapper() = default;

    data::atlas::region region;
    std::shared_ptr<gfx::atlas> atlas;
};

class atlas
{
public:
    static void register_internal_calls();

    static auto get_atlas_from_mono_object(MonoObject *object) -> std::shared_ptr<gfx::atlas>;
    static auto get_region_wrapper_from_mono_object(MonoObject *object) -> std::shared_ptr<atlas_region_wrapper>;

private:
    static void ctor(MonoObject *this_ptr, MonoString *path);
    static void ctor2(MonoObject *this_ptr, MonoObject *material_ptr, vector2f size);
    static auto get_region_by_index(MonoObject *this_ptr, int index) -> MonoObject *;
    static auto get_region_by_name(MonoObject *this_ptr, MonoString *name) -> MonoObject *;
};

} // namespace managed_interface
} // namespace mono
} // namespace aeon
