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

#include <aeon/resources/resource.h>
#include <aeon/resources/exceptions.h>
#include <aeon/resources/wrappers/atlas_resource_wrapper.h>
#include <aeon/data/atlas.h>
#include <aeon/common/logger.h>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <glm/vec2.hpp>

namespace aeon
{
namespace resources
{

class atlas : public resource
{
public:
    /*!
     * Constructor used by the atlas codec to load an atlas
     */
    explicit atlas(const std::shared_ptr<resource_wrapper> &wrapper, const std::string &material_path,
                   const data::atlas &data);

    virtual ~atlas();

    const auto &get_material_path() const
    {
        return material_path_;
    }

    const auto &get_data() const
    {
        return data_;
    }

    auto get_atlas_resource_wrapper() const
    {
        return std::dynamic_pointer_cast<atlas_resource_wrapper>(get_resource_wrapper());
    }

private:
    aeon::logger::logger logger_;

    data::atlas data_;
    std::string material_path_;
};

} // namespace resources
} // namespace aeon
