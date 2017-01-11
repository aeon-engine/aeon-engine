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

TEST(test_serializers, test_serializers_scene)
{
    serialization::scene scene;
    scene.root = std::make_unique<aeon::serialization::scene_node>();
    scene.root->position = glm::vec3();
    scene.root->rotation = glm::quat();
    scene.root->scale = glm::vec3(1.0f);
    scene.root->name = "root";

    auto camera1_node = std::make_unique<serialization::scene_node>();
    camera1_node->position = glm::vec3(0.0f, 0.0f, 6.0f);
    camera1_node->rotation = glm::quat();
    camera1_node->scale = glm::vec3(1.0f);
    camera1_node->name = "camera1_node";

    auto camera1 = std::make_unique<serialization::perspective_camera>();
    camera1->fov_y = 70.0f;
    camera1->aspect_ratio = 1280.0f / 720.0f;
    camera1->near = 0.1f;
    camera1->far = 1000.0f;
    camera1->name = "camera1";

    camera1_node->objects.push_back(std::move(camera1));
    scene.root->children.push_back(std::move(camera1_node));

    auto camera2_node = std::make_unique<serialization::scene_node>();
    camera2_node->position = glm::vec3(0.0f, 0.0f, -6.0f);
    camera2_node->rotation = glm::quat(glm::vec3(0.0f, glm::pi<float>(), 0.0f));
    camera2_node->scale = glm::vec3(1.0f);
    camera2_node->name = "camera2_node";

    auto camera2 = std::make_unique<serialization::perspective_camera>();
    camera2->fov_y = 70.0f;
    camera2->aspect_ratio = 1280.0f / 720.0f;
    camera2->near = 0.1f;
    camera2->far = 1000.0f;
    camera2->name = "camera2";

    camera2_node->objects.push_back(std::move(camera2));
    scene.root->children.push_back(std::move(camera2_node));

    auto rotation_node = std::make_unique<serialization::scene_node>();
    rotation_node->position = glm::vec3(0.0f, 0.0f, 0.0f);
    rotation_node->rotation = glm::quat();
    rotation_node->scale = glm::vec3(1.0f);
    rotation_node->name = "rotation_node";

    auto female_warrior = std::make_unique<serialization::mesh>();
    female_warrior->name = "female_warrior";
    female_warrior->path = "/resources/meshes/elementalist-warrior-female-character-f/x-elemetal.dae";

    rotation_node->objects.push_back(std::move(female_warrior));
    scene.root->children.push_back(std::move(rotation_node));

    auto skydome_node = std::make_unique<serialization::scene_node>();
    skydome_node->position = glm::vec3(0.0f, -30.0f, 0.0f);
    skydome_node->rotation = glm::quat();
    skydome_node->scale = glm::vec3(10.0f);
    skydome_node->name = "skydome_node";

    auto skydome = std::make_unique<serialization::mesh>();
    skydome->name = "skydome";
    skydome->path = "/resources/meshes/skysphere/skydome.dae";

    skydome_node->objects.push_back(std::move(skydome));
    scene.root->children.push_back(std::move(skydome_node));

    auto viewport1 = std::make_unique<serialization::viewport>();
    viewport1->name = "viewport1";
    viewport1->camera = "camera1";
    viewport1->zorder = 0;
    viewport1->rectangle = aeon::common::types::rectangle<float>(0.0f, 0.0f, 1.0f, 1.0f);
    scene.viewports.push_back(std::move(viewport1));

    auto viewport2 = std::make_unique<serialization::viewport>();
    viewport2->name = "viewport2";
    viewport2->camera = "camera2";
    viewport2->zorder = 1;
    viewport2->rectangle = aeon::common::types::rectangle<float>(0.1f, 0.1f, 0.3f, 0.3f);
    scene.viewports.push_back(std::move(viewport2));

    auto test = scene.to_json().dump();

    ASSERT_FALSE(test.empty());

    streams::file_stream filestream("test.json", streams::access_mode::write, streams::file_mode::binary);
    streams::stream_writer writer(filestream);
    writer.write_line(test);
}
