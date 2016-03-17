#pragma once

#include <audio/codec/audio_codec.h>

#include <string>
#include <cstdio>
#include <cstdint>

namespace aeon
{
namespace audio
{
class base_buffer;

// a codec should be fed data and it should output the decoded data...
class codec_wav : public codec
{
public:
    /* \note normal file access code should not be in here */
    sample_ptr decode(std::string filename) override;

    void seek(double position) override;

private:
    sample_ptr create_from_buffer(base_buffer &buffer);
};

} // namespace audio
} // namespace aeon