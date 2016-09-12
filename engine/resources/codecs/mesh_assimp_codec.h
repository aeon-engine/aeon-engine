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

#include <resources/exceptions.h>
#include <resources/codecs/mesh_codec.h>
#include <resources/mesh.h>
#include <common/logger.h>
#include <assimp/Importer.hpp>
#include <assimp/matrix4x4.h>
#include <glm/mat4x4.hpp>

struct aiNode;
struct aiScene;
struct aiMesh;

namespace aeon
{
namespace resources
{

class mesh_codec_assimp : public mesh_codec
{
public:
    mesh_codec_assimp();
    virtual ~mesh_codec_assimp() = default;

    mesh_ptr decode(resource_manager &parent, mesh_resource_wrapper_ptr wrapper) override;
    resource_encoding get_codec_type() const override;

private:
    void __decode_submeshes(const aiScene *scene, mesh &mesh_ref) const;
    void __read_index_data(aiMesh *mesh, data::index_data_buffer &indices) const;
    void __read_vertex_data(aiMesh *mesh, data::vertex_data_buffer &vertices) const;

    void __decode_scene(const aiScene *scene, mesh &mesh_ref) const;
    void __decode_scene_node(const aiNode *ai_node, mesh &mesh_ref, mesh_node &node) const;

    std::vector<submesh *> __decode_submeshes_from_scene_node(const aiNode *ai_node, mesh &mesh_ref) const;

    glm::vec3 __convert_to_glm_vec3(const aiVector3D &vector) const;
    glm::mat4 __convert_to_glm_mat4(const aiMatrix4x4 &matrix) const;

    common::types::color __convert_to_color(const aiColor4D &color) const;

    aeon::logger::logger logger_;
};

} // namespace resources
} // namespace aeon
