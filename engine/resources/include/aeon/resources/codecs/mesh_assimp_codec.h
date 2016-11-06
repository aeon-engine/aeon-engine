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

#include <aeon/resources/exceptions.h>
#include <aeon/resources/codecs/mesh_codec.h>
#include <aeon/resources/mesh.h>
#include <aeon/common/logger.h>
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

DEFINE_EXCEPTION_OBJECT(assimp_codec_decode_exception, codec_decode_exception,
                        "Error while decoding AssImp mesh resource.");

class mesh_codec_assimp : public mesh_codec
{
public:
    mesh_codec_assimp();
    virtual ~mesh_codec_assimp() = default;

    auto decode(resource_manager &parent, const std::shared_ptr<mesh_resource_wrapper> &wrapper) const
        -> std::shared_ptr<mesh> override;
    auto get_codec_type() const -> resource_encoding override;

private:
    void __decode_materials(const aiScene *scene, mesh &mesh_ref) const;
    void __decode_submeshes(const aiScene *scene, mesh &mesh_ref) const;
    void __read_index_data(aiMesh *mesh, data::index_data_buffer &indices) const;
    void __read_vertex_data(const aiMesh *mesh, data::vertex_data_buffer &vertices) const;

    void __decode_scene(const aiScene *scene, mesh &mesh_ref) const;
    void __decode_scene_node(const aiNode *ai_node, mesh &mesh_ref, mesh_node &node) const;

    auto __decode_submeshes_from_scene_node(const aiNode *ai_node, mesh &mesh_ref) const -> std::vector<submesh *>;

    auto __convert_to_glm_vec3(const aiVector3D &vector) const -> glm::vec3;
    auto __convert_to_glm_mat4(const aiMatrix4x4 &matrix) const -> glm::mat4;

    auto __convert_to_color(const aiColor4D &color) const -> common::types::color;

    logger::logger logger_;
};

} // namespace resources
} // namespace aeon
