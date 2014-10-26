/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2014 Robin Degen
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

aeon_initialize_singleton(aeon::scene_codec_manager);

scene_codec_manager::scene_codec_manager()
{

}

scene_codec_manager::~scene_codec_manager()
{

}

void scene_codec_manager::register_codec(scene_codec_ptr codec)
{
    if (!codec)
        return;

    const std::string &name = codec->get_type_name();
    registered_codecs_[name] = codec;
}

scene_ptr scene_codec_manager::decode(const std::string &name,
                                      stream_ptr stream)
{
    auto codec = registered_codecs_.find(name);

    // Could not find the codec?
    if (codec == registered_codecs_.end())
    {
        console::error("ModelCodecManager: Could not decode stream. "
            "Unknown decoder: '%s'", name.c_str());
        return nullptr;
    }

    return codec->second->decode(stream);
}

} /* namespace aeon */