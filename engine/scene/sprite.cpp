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

#include <scene/sprite.h>

#include <GL/glew.h>

namespace aeon
{
namespace scene
{

sprite::sprite(scene_manager *scene_manager, gfx::material_ptr material, int zorder)
    : render_object(render_layer::overlay, scene_manager)
    , has_z_order(zorder)
    , size_(material->get_texture()->get_size())
    , material_(material)
{
}

sprite::sprite(scene_manager *scene_manager, gfx::material_ptr material, glm::vec2 size, int zorder)
    : render_object(render_layer::overlay, scene_manager)
    , has_z_order(zorder)
    , size_(size)
    , material_(material)
{
}

sprite::sprite(scene_manager *scene_manager, gfx::material_ptr material, float width, float height, int zorder)
    : render_object(render_layer::overlay, scene_manager)
    , has_z_order(zorder)
    , size_(width, height)
    , material_(material)
{
}

void sprite::set_default_size()
{
    size_ = material_->get_texture()->get_size();
}

void sprite::set_size(glm::vec2 size)
{
    size_ = size;
}

void sprite::set_size(float width, float height)
{
    size_ = glm::vec2(width, height);
}

glm::vec2 sprite::get_size() const
{
    return size_;
}

void sprite::set_material(gfx::material_ptr texture)
{
    material_ = texture;
}

gfx::material_ptr sprite::get_material() const
{
    return material_;
}

int sprite::get_priority()
{
    return get_zorder();
}

void sprite::render()
{
    // TODO: temporary test implementation.
    material_->bind();

    glm::vec2 size_2 = size_ * 0.5f;

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-size_2.x, size_2.y, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(size_2.x, size_2.y, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(size_2.x, -size_2.y, 0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-size_2.x, -size_2.y, 0.0f);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.f, 0.6f, 0.f);
    glEnd();
}

} // namespace scene
} // namespace aeon
