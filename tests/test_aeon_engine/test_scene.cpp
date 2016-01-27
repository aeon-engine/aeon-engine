#include <gtest/gtest.h>
#include <scene/render_queue.h>
#include <aeon/platform.h>

AEON_IGNORE_WARNING(4189)

TEST(test_scene, test_render_queue_create)
{
    ASSERT_NO_THROW(aeon::scene::render_queue queue);
}
