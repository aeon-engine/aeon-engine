/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <aeon/codecs/assimp_codec.h>
#include <aeon/common/logger.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace aeon
{
namespace codecs
{

mesh_codec_assimp::mesh_codec_assimp()
    : logger_(common::logger::get_singleton(), "Codecs::AssImpCodec")
{
}

mesh_codec_assimp::~mesh_codec_assimp() = default;

auto mesh_codec_assimp::decode(const std::unique_ptr<resources::resource_provider> &provider) const
    -> std::unique_ptr<resources::mesh>
{
    AEON_LOG_DEBUG(logger_) << "Decoding AssImp mesh resource." << std::endl;

    auto input = provider->read_to_vector();

    auto importer = Assimp::Importer();
    const auto *scene = importer.ReadFileFromMemory(input.data(), input.size(), aiProcessPreset_TargetRealtime_Quality);

    if (!scene)
    {
        AEON_LOG_ERROR(logger_) << "Decoding AssImp mesh resource: " << importer.GetErrorString() << std::endl;
        throw assimp_codec_decode_exception();
    }

    // TODO: This is not a good name for the mesh.
    auto mesh_data = std::make_unique<resources::mesh>("mesh");
    __decode_materials(scene, *mesh_data);
    __decode_submeshes(scene, *mesh_data);
    __decode_scene(scene, *mesh_data);

    return mesh_data;
}

void mesh_codec_assimp::encode(std::shared_ptr<resources::mesh> /*source*/,
                               const std::unique_ptr<resources::resource_provider> & /*destination*/) const
{
    AEON_LOG_ERROR(logger_) << "Encoding through AssImp is not implemented." << std::endl;
    throw assimp_codec_encode_exception();
}

void mesh_codec_assimp::__decode_materials(const aiScene *scene, resources::mesh &mesh_ref) const
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

void mesh_codec_assimp::__decode_submeshes(const aiScene *scene, resources::mesh &mesh_ref) const
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

void mesh_codec_assimp::__decode_scene(const aiScene *scene, resources::mesh &mesh_ref) const
{
    auto ai_root_node = scene->mRootNode;
    auto matrix = __convert_to_glm_mat4(ai_root_node->mTransformation);
    auto submeshes = __decode_submeshes_from_scene_node(ai_root_node, mesh_ref);
    auto &root_node = mesh_ref.create_root_mesh_node(matrix, submeshes);

    __decode_scene_node(ai_root_node, mesh_ref, root_node);
}

void mesh_codec_assimp::__decode_scene_node(const aiNode *ai_node, resources::mesh &mesh_ref,
                                            resources::mesh_node &node) const
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

auto mesh_codec_assimp::__decode_submeshes_from_scene_node(const aiNode *ai_node, resources::mesh &mesh_ref) const
    -> std::vector<resources::submesh *>
{
    auto submeshes = std::vector<resources::submesh *>();
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

} // namespace codecs
} // namespace aeon
