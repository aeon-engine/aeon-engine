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

#pragma once

#include <aeon/scene/sprite.h>
#include <aeon/common/types/rectangle.h>
#include <aeon/scene/sprite_animation_settings.h>
#include <aeon/gfx/gfx_atlas.h>
#include <memory>

namespace aeon
{
namespace scene
{

class animated_sprite : public sprite
{
public:
    explicit animated_sprite(scene_manager *scene_manager, std::shared_ptr<gfx::atlas> atlas, int zorder,
                             const sprite_animation_settings &settings);

    virtual ~animated_sprite() = default;

    void run();
    void stop();

    void set_animation_sequence(const int index);

protected:
    void update(const float dt) override;

    sprite_animation_settings settings_;

    float frame_time_;
    int current_frame_index_;
    bool running_;

    std::vector<int> sequence_;
};

} // namespace scene
} // namespace aeon
