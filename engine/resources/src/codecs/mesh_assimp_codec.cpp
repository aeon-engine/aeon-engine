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

#include <aeon/streams.h>
#include <aeon/resources/codecs/mesh_assimp_codec.h>
#include <aeon/resources/wrappers/mesh_resource_wrapper.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <memory>

namespace aeon
{
namespace resources
{

mesh_codec_assimp::mesh_codec_assimp()
    : logger_(common::logger::get_singleton(), "Resources::AssImpCodec")
{
}

auto mesh_codec_assimp::decode(resource_manager & /*parent*/,
                               const std::shared_ptr<mesh_resource_wrapper> &wrapper) const -> std::shared_ptr<mesh>
{
    AEON_LOG_DEBUG(logger_) << "Decoding AssImp mesh resource." << std::endl;

    auto input = std::vector<std::uint8_t>();
    wrapper->read_raw(input);

    auto importer = Assimp::Importer();
    const auto *scene = importer.ReadFileFromMemory(input.data(), input.size(), aiProcessPreset_TargetRealtime_Quality);

    if (!scene)
    {
        AEON_LOG_ERROR(logger_) << "Decoding AssImp mesh resource: " << importer.GetErrorString() << std::endl;
        throw assimp_codec_decode_exception();
    }

    auto mesh_data = std::make_shared<mesh>(wrapper);
    __decode_materials(scene, *mesh_data);
    __decode_submeshes(scene, *mesh_data);
    __decode_scene(scene, *mesh_data);

    return mesh_data;
}

auto mesh_codec_assimp::get_codec_type() const -> resource_encoding
{
    return resource_encoding::mesh_assimp;
}

void mesh_codec_assimp::__decode_materials(const aiScene *scene, mesh &mesh_ref) const
{
    for (auto i = 0ul; i < scene->mNumMaterials; ++i)
    {
        auto ai_material = scene->mMaterials[i];
        auto ai_texture_path = aiString();
        if (ai_material->GetTexture(aiTextureType_DIFFUSE, 0, &ai_texture_path) == AI_SUCCESS)
        {
            auto texture_path = ai_texture_path.data;
            mesh_ref.add_material(texture_path);
        }
        else
        {
            AEON_LOG_ERROR(logger_) << "Could not get diffuse texture for material. Ignoring." << std::endl;
            // TODO: How to handle this?
            mesh_ref.add_material("/resources/materials/test.amf");
        }
    }
}

void mesh_codec_assimp::__decode_submeshes(const aiScene *scene, mesh &mesh_ref) const
{
    for (auto i = 0ul; i < scene->mNumMeshes; ++i)
    {
        auto ai_submesh = scene->mMeshes[i];

        auto indices = data::index_data_buffer();
        __read_index_data(ai_submesh, indices);

        auto vertices = data::vertex_data_buffer();
        __read_vertex_data(ai_submesh, vertices);

        auto mesh_name = ai_submesh->mName.C_Str();
        auto material = mesh_ref.get_material_by_id(ai_submesh->mMaterialIndex);

        mesh_ref.create_submesh(i, mesh_name, std::move(indices), std::move(vertices), material);
    }
}

void mesh_codec_assimp::__read_index_data(aiMesh *mesh, data::index_data_buffer &indices) const
{
    // Faces should be triangulated by aiProcess_Triangulate, so the expected indices in a face is always 3.
    const auto indices_per_face = 3;

    // Copy indices
    const auto num_faces = mesh->mNumFaces;

    indices.resize(num_faces * indices_per_face);

    auto indices_ptr = indices.data();

    unsigned int offset = 0;
    for (auto face = 0ul; face < num_faces; ++face)
    {
        auto &ai_face = mesh->mFaces[face];
        assert(ai_face.mNumIndices == indices_per_face);

        for (auto index = 0ul; index < ai_face.mNumIndices; ++index)
        {
            auto index_val = ai_face.mIndices[index];
            indices_ptr[offset++] = static_cast<unsigned int>(index_val);
        }
    }
}

void mesh_codec_assimp::__read_vertex_data(const aiMesh *mesh, data::vertex_data_buffer &vertices) const
{
    assert(mesh->mVertices != nullptr);

    const auto num_vertices = mesh->mNumVertices;
    vertices.resize(num_vertices);

    auto vertex_data_ptr = vertices.data();

    if (!mesh->HasTangentsAndBitangents())
    {
        AEON_LOG_WARNING(logger_) << "Mesh has no tangents and bitangents. Normal mapping may not work properly."
                                  << std::endl;
    }

    // Interleave the data for the GPU
    for (auto i = 0ul; i < num_vertices; ++i)
    {
        auto &data = vertex_data_ptr[i];
        data.position = __convert_to_glm_vec3(mesh->mVertices[i]);

        if (mesh->HasNormals())
            data.normal = __convert_to_glm_vec3(mesh->mNormals[i]);

        if (mesh->mTextureCoords[0])
        {
            data.uvw = __convert_to_glm_vec3(mesh->mTextureCoords[0][i]);
            data.uvw.y = 1.0f - data.uvw.y; //?
        }

        if (mesh->mColors[0])
            data.color = __convert_to_color(mesh->mColors[0][i]);

        if (mesh->HasTangentsAndBitangents())
        {
            data.tangent = __convert_to_glm_vec3(mesh->mTangents[i]);
            data.bitangent = __convert_to_glm_vec3(mesh->mBitangents[i]);
        }
    }
}

void mesh_codec_assimp::__decode_scene(const aiScene *scene, mesh &mesh_ref) const
{
    auto ai_root_node = scene->mRootNode;
    auto matrix = __convert_to_glm_mat4(ai_root_node->mTransformation);
    auto submeshes = __decode_submeshes_from_scene_node(ai_root_node, mesh_ref);
    auto &root_node = mesh_ref.create_root_mesh_node(matrix, submeshes);

    __decode_scene_node(ai_root_node, mesh_ref, root_node);
}

void mesh_codec_assimp::__decode_scene_node(const aiNode *ai_node, mesh &mesh_ref, mesh_node &node) const
{
    for (auto i = 0ul; i < ai_node->mNumChildren; ++i)
    {
        auto ai_node_child = ai_node->mChildren[i];
        auto matrix = __convert_to_glm_mat4(ai_node_child->mTransformation);

        auto submeshes = __decode_submeshes_from_scene_node(ai_node_child, mesh_ref);
        auto &child = node.create_child(ai_node_child->mName.C_Str(), matrix, submeshes);

        __decode_scene_node(ai_node_child, mesh_ref, child);
    }
}

auto mesh_codec_assimp::__decode_submeshes_from_scene_node(const aiNode *ai_node, mesh &mesh_ref) const
    -> std::vector<submesh *>
{
    auto submeshes = std::vector<submesh *>();
    for (auto i = 0ul; i < ai_node->mNumMeshes; ++i)
    {
        auto mesh_id = ai_node->mMeshes[i];
        auto submesh = mesh_ref.get_submesh_by_id(mesh_id);

        if (!submesh)
        {
            AEON_LOG_ERROR(logger_) << "Invalid submesh id '" << mesh_id << "'." << std::endl;
            throw assimp_codec_decode_exception();
        }

        submeshes.push_back(submesh);
    }

    return submeshes;
}

auto mesh_codec_assimp::__convert_to_glm_vec3(const aiVector3D &vector) const -> glm::vec3
{
    return glm::vec3(vector.x, vector.y, vector.z);
}

auto mesh_codec_assimp::__convert_to_glm_mat4(const aiMatrix4x4 &matrix) const -> glm::mat4
{
    return glm::mat4(matrix.a1, matrix.b1, matrix.c1, matrix.d1, matrix.a2, matrix.b2, matrix.c2, matrix.d2, matrix.a3,
                     matrix.b3, matrix.c3, matrix.d3, matrix.a4, matrix.b4, matrix.c4, matrix.d4);
}

auto mesh_codec_assimp::__convert_to_color(const aiColor4D &color) const -> common::types::color
{
    return common::types::color(color.r, color.g, color.b, color.a);
}

} // namespace resources
} // namespace aeon
