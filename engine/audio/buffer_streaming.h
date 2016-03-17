#pragma once

#include <audio/buffer_interface.h>
#include <audio/codec/audio_codec.h>
#include <audio/openal/openal_includes.h>

#include <string>
#include <memory>
#include <vector>
#include <thread>
#include <array>
#include <atomic>

#define AEON_AUDIO_BUFFER_COUNT 4

namespace aeon
{
namespace audio
{

/* the streaming buffer will handle the streaming of big encoded music like ogg/opus files */
class buffer_streaming : public ibuffer
{
public:
    buffer_streaming();
    ~buffer_streaming();

    void load(std::string filename, sample_format format = sample_format::auto_detect) override;
    void bind_source(aeon::audio::source *source) override;
    void unbind_source(aeon::audio::source *source) override;
    void prepare() override;

    /* acquire the openal buffers that we need to stream audio */
    void acquire_all_buffers();
    /* release the openal buffers that we have acquired */
    void release_all_buffers();

    void load_and_queue_all_buffers();
    bool load_and_queue_buffer(int buffer_index);

protected:
    void __data_thread();

private:
    aeon::audio::codec_ptr codec_;
    aeon::audio::source *source_;
    std::atomic<bool> data_thread_run_;
    std::thread data_thread_;

    /* openal buffer array */
    std::array<ALuint, AEON_AUDIO_BUFFER_COUNT> buffers_;
    /* array indicating the openal buffer contains the last data of the stream.
     * Which means we are done when that happens.
     */
    std::array<bool, AEON_AUDIO_BUFFER_COUNT> end_buffers_;

    aeon::audio::codec_stream_ptr codec_stream_;

    bool prepared_;

    uint64_t samples_processed_;
};

using buffer_streaming_ptr = std::shared_ptr<buffer_streaming>;

} // namespace audio
} // namespace aeon
