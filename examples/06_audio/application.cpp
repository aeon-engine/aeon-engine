/*
 * ROBIN DEGEN; STEVEN HOVING CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen & Steven Hoving
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
#include <scene/sprite.h>
#include <scene/sprite_batch.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

application::application()
    : aeon::desktop_application<aeon::scene::basic_scene_manager>(WINDOW_WIDTH, WINDOW_HEIGHT,
                                                                  "Example 6 - Audio")
{
    // Init resources
    get_resource_manager()->mount(std::make_shared<aeon::resources::filesystem_provider>("."), "/");

    // Set up the scene
    camera_ =
        std::make_shared<aeon::scene::orthographic_camera>(get_scene_manager(), 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    window_->create_viewport(camera_, 0);
}

void application::main(int, char *[])
{
    // Load resources
    aeon::audio::sound_ptr example_sound_mono = resource_manager_.load_sound("/resources/audio/16_44100_mono.ogg");
    aeon::audio::source_ptr source_mono = audio_device_.get_source();
    source_mono->bind(example_sound_mono);
    source_mono->play();

    aeon::audio::sound_ptr example_sound_stereo = resource_manager_.load_sound("/resources/audio/16_22050_stereo.ogg");
    aeon::audio::source_ptr source_stereo = audio_device_.get_source();
    source_stereo->bind(example_sound_stereo);
    source_stereo->play();

    // Set up scene
    aeon::scene::scene_node_ptr root_node = scene_manager_.get_root_scene_node();

    // Start the render loop
    platform_.run();
}
