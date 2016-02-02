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

#include <memory>
#include <scene/render_layer.h>

namespace aeon
{
namespace scene
{

class scene_manager;
class render_object
{
public:
    explicit render_object(int queue_group, scene_manager *scene_manager)
        : queue_group_(queue_group)
        , scene_manager_(scene_manager)
    {
    }

    virtual ~render_object() = default;

    int get_queue_group() const
    {
        return queue_group_;
    }

    /*!
     * Render objects are sorted by priority within a queue group.
     * What determines the priority is based on the type of render object.
     */
    virtual int get_priority() = 0;

    /*!
     * Called by the render queue when rendering. For some objects rendering
     * doesn't make sense (like camera's). In that case, this function must be
     * used to set up the matrices and/or buffers.
     */
    virtual void render() = 0;

protected:
    int queue_group_;
    scene_manager *scene_manager_;
};

using render_object_ptr = std::shared_ptr<render_object>;

} // namespace scene
} // namespace aeon
