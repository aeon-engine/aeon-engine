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

#include <aeon/common/cached_object.h>
#include <aeon/common/exception.h>
#include <memory>
#include <string>
#include <map>

namespace aeon
{
namespace gfx
{

DEFINE_EXCEPTION_OBJECT(gfx_material_exception, aeon::common::exception, "Material exception.");

class shader;
class texture;
class material : public common::cached_object
{
public:
    material() = default;
    virtual ~material() = default;

    virtual void bind() = 0;

    virtual auto get_shader() const -> shader * = 0;

    virtual auto get_sampler(const std::string &name) const -> texture * = 0;

    virtual auto get_sampler_by_index(const int index) const -> texture * = 0;

    /*!
     * Returns true if any of the samplers in this material has an alpha channel.
     */
    virtual auto sampler_has_alpha() const -> bool = 0;
};

} // namespace gfx
} // namespace aeon
