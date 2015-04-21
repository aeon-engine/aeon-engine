/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2014 Robin Degen
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

#include "stdafx.h"

namespace aeon
{

aeon_utility_initialize_singleton(root);

root::root(platforms::base_platform_ptr platform) :
    initialized_(false),
    running_(false)
{
    platform_ = platform;
}

root::~root()
{

}

bool root::initialize(platforms::base_platform_ptr platform)
{
    if (!instance_)
    {
        root *r = new root(platform);
        if (!r)
        {
            console::info("[Root] Could not create Root.");
            return false;
        }

        return r->__initialize_impl(platform);
    }

    console::error("[Root] Can not initialize. "
        "Initialize was already called.");
    return false;
}

void root::run()
{
    if (!initialized_)
    {
        console::error("[Root] Can't run without initializing.");
        return;
    }

    // TODO: Implement dt
    float dt = 0.1f;

    running_ = true;
    while (running_)
    {
        shader_manager::get_singleton().finalize_resources();
        texture_manager::get_singleton().finalize_resources();
        material_manager::get_singleton().finalize_resources();

        if (!platform_->pre_frame())
            break;

        for (framelistener *framelistener : frame_listeners_)
        {
            framelistener->on_frame(dt);
        }

        for (framelistener *framelistener : frame_listeners_)
        {
            framelistener->on_render();
        }

        if (!platform_->post_frame())
            break;
    }

    if (!platform_->dispose())
        console::error("[Root] Platform reported an error while disposing.");

    running_ = false;
    initialized_ = false;
}

void root::stop()
{
    running_ = false;
}

void root::add_frame_listener(framelistener *listener)
{
    frame_listeners_.push_back(listener);
}

void root::remove_frame_listener(framelistener *listener)
{
    frame_listeners_.remove(listener);
}

void root::remove_all_frame_listeners()
{
    console::debug("[Root] Removing all frame listeners.");
    frame_listeners_.clear();
}

bool root::__initialize_impl(platforms::base_platform_ptr platform)
{
    if (initialized_)
    {
        console::warning("[Root] Already initialized. "
            "Can not initialize twice.");
        return false;
    }

    console::info("[Root] Initializing.");

    if (!platform_)
    {
        console::error("[Root] Could not create platform.");
        return false;
    }

    console::info("[Root] Initializing platform.");

    if (!platform_->initialize())
    {
        console::error("[Root] Failed to initialize platform.");
        return false;
    }

    console::info("[Root] Initializing glew.");

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        console::error("[Root] Failed to initialize glew: %s", 
            glewGetErrorString(err));
        return false;
    }

    // TODO: Should we check if the singletons were properly created?
    // Register codecs
    image_codec_manager::create();

#ifdef AEON_USE_PNG
    image_codec_manager::get_singleton().register_codec(
        std::make_shared<image_codec_png>());
#endif

    scene_codec_manager::create();

#ifdef AEON_USE_ASSIMP
    scene_codec_manager::get_singleton().register_codec(
        std::make_shared<scene_codec_assimp>());
#endif

    texture_manager::create();
    shader_manager::create();
    material_manager::create();

    initialized_ = true;
    return true;
}

} // namespace aeon
