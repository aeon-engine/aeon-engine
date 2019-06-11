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

#include <aeon/scene/components/sprite.h>
#include <aeon/scene/scene_manager.h>
#include <aeon/scene/render_layer.h>
#include <aeon/math/vector3.h>
#include <aeon/math/vector4.h>

namespace aeon::scene
{

sprite::sprite(scene_manager &scene_manager, const std::shared_ptr<gfx::atlas> &atlas,
               const data::atlas::region &region, const int zorder, const std::string &name)
    : sprite(scene_manager, atlas, region, region.get_size(), zorder, name)
{
}

sprite::sprite(scene_manager &scene_manager, const std::shared_ptr<gfx::atlas> &atlas,
               const data::atlas::region &region, const math::vector2<float> size, const int zorder,
               const std::string &name)
    : component(name, render_layer::overlay, component_render_type::renderable, scene_manager)
    , has_z_order(zorder)
    , size_(size)
    , atlas_(atlas)
    , region_(region)
    , mesh_(scene_manager.get_device().create_mesh(atlas->get_material()))
{
    __upload_mesh_data();
}

auto sprite::get_axis_aligned_bounding_box() const -> common::types::rectangle<float>
{
    math::vector2<float> size_2 = {size_ * 0.5f};
    auto position = get_scene_matrix() * math::vector4<float>(0.0f, 0.0f, 0.0f, 1.0f);

    math::vector2<float> data[] = {// Bottom left
                                   math::vector2<float>{-size_2.x + position.x, size_2.y + position.y},

                                   // Bottom right
                                   math::vector2<float>{size_2.x + position.x, size_2.y + position.y},

                                   // Top left
                                   math::vector2<float>{-size_2.x + position.x, -size_2.y + position.y},

                                   // Top right
                                   math::vector2<float>{size_2.x + position.x, -size_2.y + position.y}};

    auto min_x = data[0].x;
    auto max_x = data[0].x;
    auto min_y = data[0].y;
    auto max_y = data[0].y;

    for (auto &d : data)
    {
        if (d.x < min_x)
            min_x = d.x;

        if (d.y < min_y)
            min_y = d.y;

        if (d.x > max_x)
            max_x = d.x;

        if (d.y > max_y)
            max_y = d.y;
    }

    return common::types::rectangle<float>{min_x, min_y, max_x, max_y};
}

void sprite::render(const math::mat4 &projection, const math::mat4 &view, const math::mat4 &model, const float dt)
{
    update(dt);
    mesh_->render(projection, view, model);
}

void sprite::update(const float)
{
}

void sprite::__upload_mesh_data() const
{
    __generate_and_upload_vertex_data();
    __generate_and_upload_index_data();
}

void sprite::__generate_and_upload_vertex_data() const
{
    auto size_2 = math::vector2<float>{size_ * 0.5f};
    auto vertex_data = std::vector<data::vertex_data>{
        // Bottom left
        {math::vector3<float>{-size_2.x, size_2.y, 0.0f}, math::vector3<float>{0.0f, 0.0f, 1.0f},
         math::vector3<float>{region_.u1, region_.v2, 0.0f}, common::types::color{1.0f, 1.0f, 1.0f, 1.0f}},

        // Bottom right
        {math::vector3<float>{size_2.x, size_2.y, 0.0f}, math::vector3<float>{0.0f, 0.0f, 1.0f},
         math::vector3<float>{region_.u2, region_.v2, 0.0f}, common::types::color{1.0f, 1.0f, 1.0f, 1.0f}},

        // Top left
        {math::vector3<float>{-size_2.x, -size_2.y, 0.0f}, math::vector3<float>{0.0f, 0.0f, 1.0f},
         math::vector3<float>{region_.u1, region_.v1, 0.0f}, common::types::color{1.0f, 1.0f, 1.0f, 1.0f}},

        // Top right
        {math::vector3<float>{size_2.x, -size_2.y, 0.0f}, math::vector3<float>{0.0f, 0.0f, 1.0f},
         math::vector3<float>{region_.u2, region_.v1, 0.0f}, common::types::color{1.0f, 1.0f, 1.0f, 1.0f}}};

    mesh_->upload_vertex_buffer(vertex_data, gfx::buffer_usage::dynamic_usage);
}

void sprite::__generate_and_upload_index_data() const
{
    auto index_data = std::vector<std::uint32_t>{0, 1, 2, 2, 1, 3};
    mesh_->upload_index_buffer(index_data, gfx::buffer_usage::static_usage);
}
} // namespace aeon::scene
