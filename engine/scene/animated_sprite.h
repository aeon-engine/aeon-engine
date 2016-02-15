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

#include <scene/sprite.h>
#include <common/types/rectangle.h>
#include <scene/sprite_animation_settings.h>
#include <memory>

namespace aeon
{
namespace scene
{

class animated_sprite : public sprite
{
public:
    explicit animated_sprite(scene_manager *scene_manager, sprite_batch_ptr batch, resources::atlas_ptr atlas,
                             int zorder, const sprite_animation_settings &settings);

    virtual ~animated_sprite() = default;

    void run();
    void stop();

    void set_animation_sequence(int index);

protected:
    void update(float dt) override;

    resources::atlas_ptr atlas_;
    sprite_animation_settings settings_;

    float frame_time_;
    int current_frame_index_;
    bool running_;

    std::vector<int> sequence_;
};

using animated_sprite_ptr = std::shared_ptr<animated_sprite>;

} // namespace scene
} // namespace aeon
