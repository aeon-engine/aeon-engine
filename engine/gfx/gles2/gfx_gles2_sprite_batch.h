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

#include <gfx/gfx_sprite_batch.h>
#include <gfx/gles2/gfx_gles2_buffer.h>
#include <common/logger.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

class device;
class sprite_batch : public gfx::sprite_batch
{
public:
    explicit sprite_batch(device *device, material_ptr material, std::uint16_t sprites_per_buffer);
    virtual ~sprite_batch() = default;

    void upload_sprite_buffer(const sprite_vertex *sprite_vertex_data, int count) override;

    void render(const glm::mat4x4 &projection, const glm::mat4x4 &view, const glm::mat4x4 &model) override;

private:
    void __setup_index_buffer() const;
    void __create_and_setup_vao();

    aeon::logger::logger logger_;

    gfx::buffer_ptr vertex_buffer_;
    gfx::buffer_ptr index_buffer_;
    int sprite_count_;
};

} // namespace gles2
} // namespace gfx
} // namespace aeon
