#pragma once

#include <audio/codec/audio_codec.h>
#include <audio/codec/audio_codec_file.h>

#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

#include <string>
#include <cstdio>
#include <cstdint>

namespace aeon
{
namespace audio
{
class file_buffer;

// a codec should be fed data and it should output the decoded data...
class codec_vorbis : public codec
{
public:
    codec_vorbis();
    /* \note normal file access code should not be in here */
    sample_buffer_ptr decode(std::string filename) override;
    codec_stream_ptr open_stream(std::string filename) override;
    uint64_t read(uint8_t *buffer, size_t buffer_size) override;
    void seek(double position) override;

    uint64_t get_total_size();
//private:
    sample_buffer_ptr create_from_buffer(file_buffer &buffer);

    // kinda streaming buffer something bla..
    file_buffer buffer_;
    OggVorbis_File vorbis_file_;
    vorbis_info *vorbis_info_;
};

} // namespace audio
} // namespace aeon