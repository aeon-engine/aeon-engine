/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#include "application.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const float SHIP_ROTATION_SPEED = 0.1f;
const float SHIP_ACCELERATION = 3.0f;
const float SHIP_MAX_SPEED = 2.0f;
const float SHIP_FRICTION = 2.0f;

application::application(int argc, char *argv[])
    : aeon::desktop_application<aeon::scene::basic_scene_manager>(argc, argv, WINDOW_WIDTH, WINDOW_HEIGHT,
                                                                  "Example 6 - Mesh Loading")
    , timer_(0.0f)
    , previous_mouse_x_(0.0f)
    , previous_mouse_y_(0.0f)
    , forward_speed_(0.0f)
{
    // Init resources
    get_resource_manager()->mount(std::make_shared<aeon::resources::filesystem_provider>("."), "/");

    // Attach this class as a frame listener
    get_main_window()->attach_listener(this);

    window_->set_mouse_cursor_mode(aeon::platform::mouse_cursor_mode::capture);

    // Set up the scene
    camera_ =
        std::make_shared<aeon::scene::perspective_camera>(get_scene_manager(), 45.0f, 800.0f / 600.0f, 0.1f, 10000.0f);

    window_->create_viewport(camera_, 0);

    get_platform_interface()->get_input_handler()->attach_listener(this);
}

void application::main()
{
    camera_node_position_ = get_scene_manager()->create_child_scene_node();
    camera_node_x_ = camera_node_position_->create_child_scene_node();
    camera_node_y_ = camera_node_x_->create_child_scene_node();
    camera_node_y_->attach_scene_object(camera_);

    camera_node_position_->translate(0.0f, -100.0f, 0.0f);

    /*rotation_node_ = get_scene_manager()->create_child_scene_node();
    get_scene_manager()->get_root_scene_node()->attach_child(rotation_node_);

    rotation_node_->translate(0.0f, -1.5f, -10.0f);*/

    // Load resources
    /*wave_node_ =
        get_asset_manager().load_mesh("/resources/meshes/elementalist-warrior-female-character-f/x-elemetal.dae");
    rotation_node_->attach_child(wave_node_);*/

    aeon::scene::scene_node_ptr skydome = get_asset_manager().load_mesh("resources/meshes/skysphere/skydome.dae");
    get_scene_manager()->get_root_scene_node()->attach_child(skydome);
    skydome->scale(20.0f);

    aeon::scene::scene_node_ptr city = get_asset_manager().load_mesh("resources/meshes/city/city.dae");
    get_scene_manager()->get_root_scene_node()->attach_child(city);
    city->translate(0.0f, -100.0f, 0.0f);

    // Start the render loop
    platform_.run();
}

bool application::on_frame(float dt)
{
    if (move_direction_ == ship_move_direction::forward)
    {
        forward_speed_ -= SHIP_ACCELERATION * dt;

        if (forward_speed_ < -SHIP_MAX_SPEED)
            forward_speed_ = -SHIP_MAX_SPEED;
    }
    else if (move_direction_ == ship_move_direction::reverse)
    {
        forward_speed_ += SHIP_ACCELERATION * dt;

        if (forward_speed_ > SHIP_MAX_SPEED)
            forward_speed_ = SHIP_MAX_SPEED;
    }

    // Slow down to 0.
    if (move_direction_ == ship_move_direction::none)
    {
        if (forward_speed_ > 0.0f)
        {
            forward_speed_ -= SHIP_FRICTION * dt;

            if (forward_speed_ <= 0.0f)
                forward_speed_ = 0.0f;
        }
        else if (forward_speed_ < 0.0f)
        {
            forward_speed_ += SHIP_FRICTION * dt;

            if (forward_speed_ >= 0.0f)
                forward_speed_ = 0.0f;
        }
    }

    camera_node_position_->translate(0.0f, 0.0f, forward_speed_);

    return true;
}

void application::on_keyboard_event(aeon::platform::platform_window * /*window*/, aeon::platform::keyboard_key key,
    aeon::platform::keyboard_key_state key_state, int /*modifier*/)
{
    if (key_state == aeon::platform::keyboard_key_state::pressed)
    {
        if (key == aeon::platform::keyboard_key::key_escape)
        {
            platform_.stop();
        }

        /*if (key == aeon::platform::keyboard_key::key_q)
        {
            aeon::platform::mouse_cursor_mode mode = window->get_mouse_cursor_mode();
            window->set_mouse_cursor_mode(mode == aeon::platform::mouse_cursor_mode::normal ?
                aeon::platform::mouse_cursor_mode::capture : aeon::platform::mouse_cursor_mode::normal);
        }*/
    }

    if (key == aeon::platform::keyboard_key::key_up)
    {
        if (key_state == aeon::platform::keyboard_key_state::pressed)
            move_direction_ = ship_move_direction::forward;
        else
            move_direction_ = ship_move_direction::none;
    }

    if (key == aeon::platform::keyboard_key::key_down)
    {
        if (key_state == aeon::platform::keyboard_key_state::pressed)
            move_direction_ = ship_move_direction::reverse;
        else
            move_direction_ = ship_move_direction::none;
    }
}

void application::on_mouse_move_event(aeon::platform::platform_window * /*window*/, float x, float y)
{
    float deltax = x - previous_mouse_x_;
    float deltay = y - previous_mouse_y_;
    previous_mouse_x_ = x;
    previous_mouse_y_ = y;

    camera_node_x_->rotate(0.0f, deltax * 0.00001f, 0.0f);
    camera_node_y_->rotate(deltay * 0.00001f, 0.0f, 0.0f);

    AEON_LOG_MESSAGE(get_logger()) << "X: " << deltax << " Y: " << deltay << std::endl;
}
