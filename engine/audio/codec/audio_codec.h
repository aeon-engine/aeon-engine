#pragma once

#include <audio/audio_sample_buffer.h>
#include <common/buffer.h>
#include <string>

namespace aeon
{
namespace audio
{
/*!
 * Wrapper class that contains 'sample' information about the audio sample.
 * As it contains the channel count, bits per sample and the sample rate it
 * has enough information to serve openal in playing that sample.
 */
class sample_info
{
public:
    sample_info() = default;
    sample_info(int channel_count, int bits_per_sample, int sample_rate)
        : channel_count_(channel_count)
        , bits_per_sample_(bits_per_sample)
        , sample_rate_(sample_rate)
    {
    }

    int channel_count_ = 0;
    int bits_per_sample_ = 0;
    int sample_rate_ = 0;
};

class codec_stream;
using codec_stream_ptr = std::unique_ptr<codec_stream>;

class codec
{
public:
    codec() = default;
    virtual ~codec() = default;

    /*! open and decode the whole file */
    virtual sample_buffer_ptr decode(std::string filename) = 0;
    virtual sample_buffer_ptr decode(common::buffer_u8 &data) = 0;

    /*! open for streaming decode*/
    virtual codec_stream_ptr open_stream(std::string /*filename*/) { return nullptr; };
    virtual codec_stream_ptr open_stream(common::buffer_u8 & /*data*/) { return nullptr; };

    /*! read/fill/decode into a buffer */
    virtual uint64_t read(uint8_t * /*buffer*/, size_t /*buffer_size*/) { return 0; };

    /*! seek (in PCM time) */
    virtual void seek(double position) = 0;
};

using codec_ptr = std::unique_ptr<codec>;

class codec_stream
{
public:
    codec_stream(codec *_codec, int channel_count, int bits_per_sample, int sample_rate)
        : codec_(_codec)
        , channel_count_(channel_count)
        , bits_per_sample_(bits_per_sample)
        , sample_rate_(sample_rate)
    {
    }

    uint64_t read(uint8_t *buffer, size_t buffer_size)
    {
        return codec_->read(buffer, buffer_size);
    }

    codec *codec_;

    // i'm a lazy mofo
    int channel_count_;
    int bits_per_sample_;
    int sample_rate_;
};

using codec_stream_ptr = std::unique_ptr<codec_stream>;



} // namespace audio
} // namespace aeon
