#pragma once

#include <audio/sample_buffer.h>

namespace aeon
{
namespace audio
{

class codec_stream;
using codec_stream_ptr = std::unique_ptr<codec_stream>;


class codec
{
public:
    virtual sample_buffer_ptr decode(std::string filename) = 0;
    virtual codec_stream_ptr open_stream(std::string /*filename*/) { return nullptr; };
    virtual uint64_t read(uint8_t * /*buffer*/, size_t /*buffer_size*/) { return 0; };
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
