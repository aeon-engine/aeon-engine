#include "stdafx.h"

namespace aeon
{


model_codec_assimp::model_codec_assimp()
{

}

model_codec_assimp::~model_codec_assimp()
{

}

aeon::model_ptr model_codec_assimp::decode(stream_ptr stream)
{
    return nullptr;
}

std::string model_codec_assimp::get_type_name() const
{
    return "ASSIMP";
}

} /* namespace aeon */
