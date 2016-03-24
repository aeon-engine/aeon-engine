#include "audio_buffer_streaming.h"
#include "audio_source.h"
#include "codec/audio_codec_wav.h"
#include "codec/audio_codec_vorbis.h"
#include "openal/openal_check.h"
#include "openal/openal_includes.h"
#include "openal/openal_format.h"

namespace aeon
{
namespace audio
{
buffer_streaming::buffer_streaming()
    : codec_()
    , source_(nullptr)
    , data_thread_run_(false)
    , data_thread_()
    , buffers_()
    , end_buffers_()
    , codec_stream_()
    , prepared_(false)
    , samples_processed_(0)
{
}

buffer_streaming::~buffer_streaming()
{
    data_thread_run_ = false;
    data_thread_.join();

    source_->unbind();
}

void buffer_streaming::load(std::string filename, sample_format format /*= sample_format::auto_detect*/)
{
    if (format == sample_format::auto_detect)
        format = format_by_file_extention(filename);

    // do magic
    // do something related to formats
    
    if (format == sample_format::wav)
        codec_ = std::make_unique<aeon::audio::codec_wav>();
    else if (format == sample_format::ogg)
        codec_ = std::make_unique<aeon::audio::codec_vorbis>();
    else
        __debugbreak();

    codec_stream_ = codec_->open_stream(filename);
    if (!codec_stream_)
    {
        printf("aeon::audio::buffer unable to stream: '%s'\n", filename.c_str());
        return;
    }
}

void buffer_streaming::bind_source(aeon::audio::source *source)
{
    source_ = source;
}

void buffer_streaming::unbind_source(aeon::audio::source * /*source*/)
{
    source_ = nullptr;
}

void buffer_streaming::load_and_queue_all_buffers()
{
    for (int i = 0; i < buffers_.size(); ++i)
        load_and_queue_buffer(i);
}

bool buffer_streaming::load_and_queue_buffer(int buffer_index)
{
    /* \todo the size of this buffer needs to represent 250 ms */
    uint8_t buffer[4096];
    size_t buffer_length = codec_stream_->read(buffer, sizeof(buffer));
    if (buffer_length == 0)
        end_buffers_[buffer_index] = true;

    printf("aeon::audio::stream, loaded streaming buffer: %I64u bytes\n", buffer_length);

    if (buffer_length > 0)
    {
        auto al_buffer = buffers_[buffer_index];

        /* \todo we don't have to fetch the openal format every time */
        ALenum buffer_format = get_openal_format(codec_stream_->channel_count_, codec_stream_->bits_per_sample_);

        // Fill the buffer
        //ALsizei size = static_cast<ALsizei>(data.sampleCount) * sizeof(Int16);
        al_check(alBufferData(al_buffer, buffer_format, buffer, (ALsizei)buffer_length, codec_stream_->sample_rate_));

        // Push it into the sound queue
        al_check(alSourceQueueBuffers(source_->get_al_source(), 1, &al_buffer));
    }

    return false;
}

void buffer_streaming::__data_thread()
{
    printf("buffer streaming data thread started\n");

    while (data_thread_run_)
    {
        ALint buffers_processed = 0;
        al_check(alGetSourcei(source_->get_al_source(), AL_BUFFERS_PROCESSED, &buffers_processed));

        while (buffers_processed--)
        {
            // Pop the first unused buffer from the queue
            ALuint buffer;
            al_check(alSourceUnqueueBuffers(source_->get_al_source(), 1, &buffer));

            // Find its number
            unsigned int buffer_index = 0;
            for (int i = 0; i < buffers_.size(); ++i)
            {
                if (buffers_[i] == buffer)
                {
                    buffer_index = i;
                    break;
                }
            }

            // Retrieve its size and add it to the samples count
            if (end_buffers_[buffer_index])
            {
                // This was the last buffer: reset the sample count
                samples_processed_ = 0;
                end_buffers_[buffer_index] = false;
            }
            else
            {
                ALint size, bits;
                al_check(alGetBufferi(buffer, AL_SIZE, &size));
                al_check(alGetBufferi(buffer, AL_BITS, &bits));
                samples_processed_ += size / (bits / 8);
            }

            // Fill it and push it back into the playing queue
            //if (load_and_queue_buffer(bufferNum))
                //requestStop = true;

            load_and_queue_buffer(buffer_index);
        }

        // sleep a bit
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    release_all_buffers();

    data_thread_run_ = false;
    prepared_ = false;
    printf("buffer streaming data thread stopped\n");
}

void buffer_streaming::prepare()
{
    printf("aeon::audio::stream prepare\n");
    if (data_thread_run_)
    {
        data_thread_run_ = false;
        prepared_ = false;

        // check if the buffer stream has already played a audio file and we want to repeat. If that is the case, we should wait until the streaming thread has finished.
        if (data_thread_.joinable())
            data_thread_.join();

        // rewind the codec / audio file to begin...
        codec_->seek(0.0);
    }

    // check if streaming buffer is already prepared...
    if (prepared_)
        return;

    prepared_ = true;

    // generate the openal buffers only when we are actually going to play
    acquire_all_buffers();

    // make sure all our buffers are loaded and queued... before pressing play
    load_and_queue_all_buffers();

    data_thread_run_ = true;
    data_thread_ = std::thread(&buffer_streaming::__data_thread, this);
}

void buffer_streaming::acquire_all_buffers()
{
    for (auto &buffer : buffers_)
        al_check(alGenBuffers(1, &buffer));
}

void buffer_streaming::release_all_buffers()
{
    for (auto &buffer : buffers_)
        al_check(alDeleteBuffers(1, &buffer));
}

} // namespace audio
} // namespace aeon
