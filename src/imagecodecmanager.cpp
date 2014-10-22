#include "stdafx.h"

aeon_initialize_singleton(aeon::image_codec_manager);

namespace aeon
{

image_codec_manager::image_codec_manager()
{

}

image_codec_manager::~image_codec_manager()
{

}

void image_codec_manager::register_codec(image_codec_ptr codec)
{
    if(!codec)
        return;
    
    const std::string &name = codec->get_type_name();
    registered_codecs_[name] = codec;
}

image_ptr image_codec_manager::decode(const std::string &name, 
    stream_ptr stream)
{
    auto codec = registered_codecs_.find(name);

    // Could not find the codec?
    if(codec == registered_codecs_.end())
    {
        console::error("ImageCodecManager: Could not decode stream. "
            "Unknown decoder: '%s'", name.c_str());
        return aeon_empty_image;
    }

    return codec->second->decode(stream);
}

} /* namespace aeon */
