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
#include <common/buffer.h>
#include <resources/resource_encoding.h>
#include <resources/codecs/codec.h>
#include <audio/audio.h>
#include <resources/wrappers/sound_resource_wrapper.h>
#include <common/logger.h>

namespace aeon
{
namespace resources
{

class material_resource_wrapper;
class resource_manager;

class sound_codec : public codec
{
public:
    sound_codec();
    virtual ~sound_codec() = default;

    resource_encoding get_codec_type() const override;

    audio::sound_ptr decode(resource_manager &parent, sound_resource_wrapper_ptr wrapper);
    audio::stream_ptr open_stream(resource_manager &parent, stream_resource_wrapper_ptr wrapper);

private:
    aeon::logger::logger logger_;
};

using sound_codec_ptr = std::unique_ptr<sound_codec>;

} // namespace resources
} // namespace aeon
