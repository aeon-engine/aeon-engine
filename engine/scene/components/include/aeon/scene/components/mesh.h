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

#include <aeon/scene/component.h>
#include <aeon/gfx/gfx_mesh.h>
#include <aeon/gfx/gfx_material.h>
#include <memory>

namespace aeon
{
namespace scene
{

class mesh : public component
{
public:
    explicit mesh(scene_manager &scene_manager, const std::shared_ptr<gfx::material> &material,
                  const std::vector<data::vertex_data> &vertex_data, const std::vector<std::uint32_t> &index_data,
                  const std::string &name = "");

    virtual ~mesh();

private:
    void render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model,
                const float dt) override;

    std::unique_ptr<gfx::mesh> mesh_;
};

} // namespace scene
} // namespace aeon
