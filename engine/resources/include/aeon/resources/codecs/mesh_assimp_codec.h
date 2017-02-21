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
