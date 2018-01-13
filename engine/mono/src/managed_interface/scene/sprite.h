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

#include <managed_interface/core/object.h>
#include <managed_interface/core/types.h>
#include <managed_interface/assets/atlas.h>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

class sprite
{
public:
    static void register_internal_calls();

private:
    static void ctor(MonoObject *this_ptr, std::shared_ptr<managed_interface::atlas_region_wrapper> region, int z_order,
                     std::string name);
    static void ctor2(MonoObject *this_ptr, std::shared_ptr<managed_interface::atlas_region_wrapper> region,
                      glm::vec2 size, int z_order, std::string name);
};

} // namespace managed_interface
} // namespace mono
} // namespace aeon
