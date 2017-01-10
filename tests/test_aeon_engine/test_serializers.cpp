/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#include <gtest/gtest.h>
#include <aeon/platform.h>
#include <aeon/streams.h>
#include <memory>
#include <aeon/serialization/serialization.h>

AEON_IGNORE_VS_WARNING(4189)

using namespace aeon;

TEST(test_serializers, test_serializers_world)
{
    serialization::world world;
    world.root = std::make_unique<aeon::serialization::scene_node>();
    world.root->position = glm::vec3();
    world.root->rotation = glm::quat();
    world.root->scale = glm::vec3(1.0f);
    world.root->name = "root";

    auto mesh1_node = std::make_unique<serialization::scene_node>();
    mesh1_node->position = glm::vec3(0.0f, 2.0f, 0.0f);
    mesh1_node->rotation = glm::quat();
    mesh1_node->scale = glm::vec3(1.0f);
    mesh1_node->name = "mesh1_node";

    auto mesh1 = std::make_unique<serialization::mesh>();
    mesh1->name = "Mesh1";
    mesh1->path = "/resources/meshes/mesh1.dae";

    mesh1_node->objects.push_back(std::move(mesh1));
    world.root->children.push_back(std::move(mesh1_node));

    auto camera_node = std::make_unique<serialization::scene_node>();
    camera_node->position = glm::vec3(0.0f, 2.0f, -10.0f);
    camera_node->rotation = glm::quat();
    camera_node->scale = glm::vec3(1.0f);
    camera_node->name = "camera_node";

    auto camera1 = std::make_unique<serialization::perspective_camera>();
    camera1->fov_y = 90.0f;
    camera1->aspect_ratio = 1280.0f / 720.0f;
    camera1->near = 0.1f;
    camera1->far = 1000.0f;
    camera1->name = "main_camera";

    camera_node->objects.push_back(std::move(camera1));
    world.root->children.push_back(std::move(camera_node));

    auto test = world.to_json().dump();

    ASSERT_FALSE(test.empty());

    streams::file_stream filestream("test.json", streams::access_mode::write, streams::file_mode::binary);
    streams::stream_writer writer(filestream);
    writer.write_line(test);
}
