/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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

#include "stdafx.h"

namespace aeon
{

scene_codec_assimp::scene_codec_assimp()
{

}

scene_codec_assimp::~scene_codec_assimp()
{

}

aeon::scene_ptr scene_codec_assimp::decode(aeon::streams::stream_ptr stream)
{
    buffer_ptr buffer = std::make_shared<aeon::buffer>(stream->size());
    stream->read((std::uint8_t *) buffer->get(), stream->size());

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFileFromMemory(buffer->get(), buffer->size(),
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    if (!scene)
    {
        console::error("[ModelCodec]: Could not decode model. "
            "Assimp reported an error: %s",
            importer.GetErrorString()
        );
        return nullptr;
    }

    return nullptr;
}

std::string scene_codec_assimp::get_type_name() const
{
    return "ASSIMP";
}

} // namespace aeon
