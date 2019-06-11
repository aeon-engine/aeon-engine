/*
 * Copyright (c) 2012-2018 Robin Degen
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

#include <aeon/codecs/basic_codec.h>
#include <aeon/resources/mesh.h>
#include <aeon/logger/logger.h>
#include <aeon/math/vector3.h>
#include <aeon/math/mat4.h>
#include <assimp/Importer.hpp>
#include <assimp/matrix4x4.h>

struct aiNode;
struct aiScene;
struct aiMesh;

namespace aeon::codecs
{

DEFINE_EXCEPTION_OBJECT(assimp_codec_decode_exception, codec_exception, "Error while decoding AssImp mesh resource.");
DEFINE_EXCEPTION_OBJECT(assimp_codec_encode_exception, codec_exception, "Error while encoding AssImp mesh resource.");

class mesh_codec_assimp : public basic_codec<resources::mesh>
{
public:
    mesh_codec_assimp();
    virtual ~mesh_codec_assimp();

    auto decode(const std::unique_ptr<resources::resource_provider> &provider) const
        -> std::unique_ptr<resources::mesh> override;
    void encode(std::shared_ptr<resources::mesh> source,
                const std::unique_ptr<resources::resource_provider> &destination) const override;

private:
    void __decode_materials(const aiScene *scene, resources::mesh &mesh_ref) const;
    void __decode_submeshes(const aiScene *scene, resources::mesh &mesh_ref) const;
    void __read_index_data(aiMesh *mesh, data::index_data_buffer &indices) const;
    void __read_vertex_data(const aiMesh *mesh, data::vertex_data_buffer &vertices) const;

    void __decode_scene(const aiScene *scene, resources::mesh &mesh_ref) const;
    void __decode_scene_node(const aiNode *ai_node, resources::mesh &mesh_ref, resources::mesh_node &node) const;

    auto __decode_submeshes_from_scene_node(const aiNode *ai_node, resources::mesh &mesh_ref) const
        -> std::vector<resources::submesh *>;

    auto __convert_to_glm_vec3(const aiVector3D &vector) const -> math::vector3<float>;
    auto __convert_to_glm_mat4(const aiMatrix4x4 &matrix) const -> math::mat4;

    auto __convert_to_color(const aiColor4D &color) const -> common::types::color;

    logger::logger logger_;
};

} // namespace aeon::codecs
