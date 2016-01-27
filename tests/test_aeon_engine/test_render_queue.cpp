#include <gtest/gtest.h>
#include <scene/render_queue.h>
#include <scene/sprite.h>
#include <aeon/platform.h>

AEON_IGNORE_WARNING(4189)

using namespace aeon;

TEST(test_render_queue, test_render_queue_create)
{
    ASSERT_NO_THROW(scene::render_queue queue);
}

TEST(test_render_queue, test_render_queue_sort_by_group)
{
    scene::render_queue queue;

    for (int i = 0; i <= 100; ++i)
    {
        int group_id = 100 - i;

        // We abuse width for checking the order later on.
        scene::sprite_ptr s = std::make_shared<aeon::scene::sprite>(nullptr, glm::vec2(group_id, 10));
        queue.add_render_object(s, group_id);
    }

    int group_id = 100;
    for(auto obj : queue)
    {
        ASSERT_EQ(group_id, obj.first);

        auto sprite = std::dynamic_pointer_cast<scene::sprite>(obj.second);
        ASSERT_EQ(group_id, sprite->get_size().x);

        --group_id;
    }

    queue.sort();

    group_id = 0;
    for (auto obj : queue)
    {
        ASSERT_EQ(group_id, obj.first);

        auto sprite = std::dynamic_pointer_cast<scene::sprite>(obj.second);
        ASSERT_EQ(group_id, sprite->get_size().x);

        ++group_id;
    }
}

TEST(test_render_queue, test_render_queue_sort_by_group_and_sprite_z_order)
{
    scene::render_queue queue;

    for (int i = 0; i <= 100; ++i)
    {
        int group_id = 100 - i;
        for (int j = 0; j <= 100; ++j)
        {
            int zorder = 100 - j;

            // We abuse width and height for checking the order later on.
            scene::sprite_ptr s = std::make_shared<aeon::scene::sprite>(nullptr, glm::vec2(group_id, zorder), zorder);
            queue.add_render_object(s, group_id);
        }
    }

    int group_id = 100;
    int zorder = 100;
    for (auto obj : queue)
    {
        if (zorder == 100)
            ASSERT_EQ(group_id, obj.first);

        auto sprite = std::dynamic_pointer_cast<scene::sprite>(obj.second);
        ASSERT_EQ(group_id, sprite->get_size().x);
        ASSERT_EQ(zorder, sprite->get_size().y);

        --zorder;

        if (zorder < 0)
        {
            --group_id;
            zorder = 100;
        }
    }

    queue.sort();

    group_id = 0;
    zorder = 0;
    for (auto obj : queue)
    {
        if (zorder == 0)
            ASSERT_EQ(group_id, obj.first);

        auto sprite = std::dynamic_pointer_cast<scene::sprite>(obj.second);
        ASSERT_EQ(group_id, sprite->get_size().x);
        ASSERT_EQ(zorder, sprite->get_size().y);

        ++zorder;

        if (zorder > 100)
        {
            ++group_id;
            zorder = 0;
        }
    }
}
