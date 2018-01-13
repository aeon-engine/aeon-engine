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

#include "application.h"
#include <aeon/application/default_context.h>
#include <aeon/resources/providers/filesystem_collection_provider.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

application::application()
    : aeon::application::desktop_application(aeon::application::default_context::create())
    , timer_(0.0f)
{
    // Init resources
    get_resource_manager().mount(
        std::make_unique<aeon::resources::filesystem_collection_provider>(get_io_interface(), "."), "/");

    // Attach this class as a frame listener
    get_main_window().attach_listener(this);
}

void application::main()
{
    auto root_node = get_scene_manager().get_root_scene_node();

    auto world = get_asset_manager().load_scene("/resources/scenes/testworld.asc");
    root_node->attach_child(world);

    camera_ = world->find_component_by_name<aeon::scene::perspective_camera>("camera1");
    get_main_window().create_viewport(camera_, "viewport1", 0);

    camera2_ = world->find_component_by_name<aeon::scene::perspective_camera>("camera2");
    aeon::common::types::rectangle<float> smaller_viewport_rect(0.1f, 0.1f, 0.3f, 0.3f);
    get_main_window().create_viewport(camera2_, smaller_viewport_rect, "viewport2", 1);

    rotation_node_ = root_node->find_child_by_name("rotation_node");

    staff_node_ = root_node->find_child_by_name("SUN Onlin7");
    staff_node_->set_position(0.5f, 0.0f, 0.0f);

    // Start the render loop
    get_platform().run();
}

auto application::on_frame_begin(const float dt) -> bool
{
    rotation_node_->rotate(0.0f, -0.1f * dt, 0.0f);
    staff_node_->rotate(-0.3f * dt, 0.0f, 0.0f);
    return true;
}
