#include <audio/codec/audio_codec_vorbis.h>

// we will always decode vorbis as 16 bit audio
#define AEON_AUDIO_CODEC_VORBIS_SAMPLE_SIZE 2

namespace aeon
{
namespace audio
{

codec_vorbis::codec_vorbis()
    : buffer_()
    , vorbis_file_()
    , vorbis_info_(nullptr)
{
}

sample_buffer_ptr codec_vorbis::decode(std::string filename)
{
    file_buffer buffer(filename);

    sample_buffer_ptr result = create_from_buffer(buffer);
    return result;
}

#if 0
// todo implement create_from_buffer with stream + read
#else
sample_buffer_ptr codec_vorbis::create_from_buffer(file_buffer &buffer)
{
    OggVorbis_File vorbis_file;
    int res;

    res = ov_open_callbacks(&buffer, &vorbis_file, nullptr, 0,
        {
            [](void *ptr, size_t size, size_t nmemb, void *datasource) -> size_t
            {return ((file_buffer*)datasource)->read(ptr, size, nmemb);},

            [](void *datasource, ogg_int64_t offset, int whence) -> int
            {return ((file_buffer*)datasource)->seek(offset, whence);},

            nullptr,

            [](void *datasource) -> long
            {return (long)((file_buffer*)datasource)->tell();},
        }
    );

    if (res != 0)
        return nullptr;

    std::vector<uint8_t> pcm_buffer;

    // Get some information about the file (Channels, Format, and Frequency)
    vorbis_info *psVorbisInfo = ov_info(&vorbis_file, -1);
    if (!psVorbisInfo)
    {
        printf("aeon::audio::codec_vorbis, unable to get file info\n");
        return nullptr;
    }

    int pcm_buff_multiplier = psVorbisInfo->channels * AEON_AUDIO_CODEC_VORBIS_SAMPLE_SIZE;
    uint64_t pcm_buffer_len = ov_pcm_total(&vorbis_file, -1) * pcm_buff_multiplier;

    pcm_buffer.resize(pcm_buffer_len);

    int current_section;
    long decode_size;
    size_t bytes_done = 0;
    while (1)
    {
        decode_size = ov_read(&vorbis_file, (char*)&pcm_buffer[bytes_done], (int)(pcm_buffer.size() - bytes_done), 0, AEON_AUDIO_CODEC_VORBIS_SAMPLE_SIZE, 1, &current_section);
        if (decode_size > 0)
        {
            bytes_done += decode_size;

            if (bytes_done >= pcm_buffer.size())
                break;
        }
        else
        {
            break;
        }
    }

    sample_buffer_ptr result = std::make_unique<sample_buffer>(
        psVorbisInfo->channels,
        AEON_AUDIO_CODEC_VORBIS_SAMPLE_SIZE * 8, // always 16 bits!
        psVorbisInfo->rate,
        pcm_buffer.data(),
        pcm_buffer.size());

    return result;
}
#endif

codec_stream_ptr codec_vorbis::open_stream(std::string filename)
{
    // blegh...
    buffer_ = aeon::audio::file_buffer(filename);

    int res = ov_open_callbacks(&buffer_, &vorbis_file_, nullptr, 0, {
        [](void *ptr, size_t size, size_t nmemb, void *datasource) -> size_t
        {return ((file_buffer*)datasource)->read(ptr, size, nmemb); },

        [](void *datasource, ogg_int64_t offset, int whence) -> int
        {return ((file_buffer*)datasource)->seek(offset, whence); },

        nullptr,

        [](void *datasource) -> long
        {return (long)((file_buffer*)datasource)->tell(); },
    }
    );

    if (res != 0)
        return nullptr;

    // Get some information about the file (Channels, Format, and Frequency)
    vorbis_info_ = ov_info(&vorbis_file_, -1);
    if (!vorbis_info_)
    {
        printf("aeon::audio::codec_vorbis, unable to get file info\n");
        return nullptr;
    }

    return std::make_unique<codec_stream>(
        this,
        vorbis_info_->channels,
        AEON_AUDIO_CODEC_VORBIS_SAMPLE_SIZE * 8, // always 16 bits!
        vorbis_info_->rate
        );
}

uint64_t codec_vorbis::read(uint8_t *buffer, size_t buffer_size)
{
    uint8_t *pcm_buffer = buffer;
    size_t pcm_buffer_size = buffer_size;

    int current_section;
    long decode_size;
    size_t bytes_done = 0;
    while (1)
    {
        decode_size = ov_read(&vorbis_file_, (char*)&pcm_buffer[bytes_done], int(pcm_buffer_size - bytes_done), 0, AEON_AUDIO_CODEC_VORBIS_SAMPLE_SIZE, 1, &current_section);
        if (decode_size > 0)
        {
            bytes_done += decode_size;

            if (bytes_done >= pcm_buffer_size)
                break;
        }
        else
        {
            break;
        }
    }

    return bytes_done;
}

void codec_vorbis::seek(double position)
{
    ov_time_seek(&vorbis_file_, position);
}

uint64_t codec_vorbis::get_total_size()
{
    if (vorbis_info_ == nullptr)
        return 0;

    int pcm_buff_multiplier = vorbis_info_->channels * AEON_AUDIO_CODEC_VORBIS_SAMPLE_SIZE;
    uint64_t pcm_buffer_len = ov_pcm_total(&vorbis_file_, -1) * pcm_buff_multiplier;
    return pcm_buffer_len;
}

} // namespace audio
} // namespace aeon



