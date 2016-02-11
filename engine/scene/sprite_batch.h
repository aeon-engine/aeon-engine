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

#include <scene/scene_object.h>
#include <memory>

namespace aeon
{
namespace scene
{

class sprite_batch : public scene_object
{
public:
    sprite_batch(scene_manager *scene_manager);
    virtual ~sprite_batch() = default;

protected:
    virtual void render(float dt) override;
};

using sprite_batch_ptr = std::shared_ptr<sprite_batch>;

} // namespace scene
} // namespace aeon
