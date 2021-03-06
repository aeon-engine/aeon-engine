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

#include <aeon/gfx/gfx_material.h>
#include <aeon/data/atlas.h>
#include <aeon/logger/logger.h>
#include <aeon/common/cached_object.h>
#include <aeon/common/exception.h>
#include <aeon/math/vector2.h>
#include <memory>

namespace aeon::gfx
{

DEFINE_EXCEPTION_OBJECT(atlas_exception, common::exception, "Generic Atlas exception.");

class atlas : public common::cached_object, public std::enable_shared_from_this<atlas>
{
    friend class gfx_atlas_manager;

public:
    explicit atlas(const std::shared_ptr<material> &material, const data::atlas &atlas);
    explicit atlas(const std::shared_ptr<material> &material, math::vector2<float> sprite_size);
    virtual ~atlas() = default;

    auto get_region_by_index(int index) const -> data::atlas::region;
    auto get_region_by_name(const std::string &name) const -> data::atlas::region;

    auto get_material() const -> std::shared_ptr<material>;

private:
    void __calculate_atlas_regions(math::vector2<float> sprite_size);

    logger::logger logger_;

    std::shared_ptr<material> material_;
    data::atlas atlas_;
};

} // namespace aeon::gfx
