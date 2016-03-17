#include <audio/codec/audio_codec_wav.h>
#include <audio/codec/audio_codec_file.h>
#include <audio/openal/openal_includes.h>

#define WAVE_FORMAT_PCM 0x0001 /* PCM */

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif

/******************************* WAV specific headers *************************/
struct RIFF_Header
{
    uint32_t chunk_id;
    int32_t chunk_size;
    uint32_t format;
};

struct WAVE_Format
{
    uint32_t sub_chunk_id;
    int32_t sub_chunk_size;
    int16_t audio_format; // Format type: 1 = PCM, 2 = ADPCM
    int16_t num_channels; // Number of channels (i.e. mono, stereo...)
    int32_t sample_rate; // Sample rate, 44100 or 22050 or 11025 Hz.
    int32_t byte_rate;
    int16_t block_align; // Block size of data = Channels times BYTES per sample.
    int16_t bits_per_sample; // Number of bits per sample (mono).
};

struct WAVE_Data
{
    uint32_t sub_chunk_id;
    int32_t sub_chunk_size; // stores the size of the data block
};

struct RIFF_SubChunk
{
    uint32_t sub_chunk_id;
    int32_t sub_chunk_size; // stores the size of the data block
};

#ifdef _MSC_VER
#pragma pack(pop)
#else
__attribute__((packed));
#endif

/*********************** WAV specific utility functions************************/
static
const uint8_t *find_chunk(const uint8_t *start, const uint8_t *end, uint32_t chunk_id)
{
    RIFF_SubChunk chunk;
    const uint8_t *ptr = start;
    while (ptr < (end - sizeof(RIFF_SubChunk)))
    {
        memcpy(&chunk, ptr, sizeof(RIFF_SubChunk));
        if (chunk.sub_chunk_id == chunk_id)
            return ptr;

        ptr += sizeof(RIFF_SubChunk) + chunk.sub_chunk_size;
    }
    return nullptr;
}

template<typename T>
inline const uint8_t *read_subchunk(T& dest, const uint8_t *& ptr)
{
    const uint8_t *ret;
    memcpy(&dest, ptr, sizeof(T));
    ptr += sizeof(RIFF_SubChunk);
    ret = ptr;
    ptr += dest.sub_chunk_size;
    return ret;
}

/****************************** utility functions *****************************/
constexpr
uint32_t fourcc(char const p[5])
{
    return (p[3] << 24) | (p[2] << 16) | (p[1] << 8) | p[0];
}

namespace aeon
{
namespace audio
{

sample_ptr codec_wav::decode(std::string filename)
{
    file_buffer buffer(filename);

    sample_ptr result = create_from_buffer(buffer);

    return result;
}

sample_ptr codec_wav::create_from_buffer(base_buffer &buffer)
{
    /* \note totally not safe, maybe from a functional perspective this is safe
     * but the 'NOT safe' problem actually comes from the readability.
     */
    const uint8_t* start = (const uint8_t*)buffer.data();
    const uint8_t* end = start + buffer.size();
    const uint8_t* ptr = start;
    RIFF_Header riff_header;
    WAVE_Format wave_format;
    WAVE_Data wave_data;

    memcpy(&riff_header, ptr, sizeof(RIFF_Header));
    ptr += sizeof(RIFF_Header);

    /* \todo throwing exceptions or doing it C style? */
    if (riff_header.chunk_id != fourcc("RIFF")
        || riff_header.format != fourcc("WAVE"))
        return nullptr;

    ptr = find_chunk(ptr, end, fourcc("fmt "));
    if (!ptr)
        return nullptr;

    read_subchunk(wave_format, ptr);

    if (wave_format.audio_format != WAVE_FORMAT_PCM)
        return nullptr;

    ptr = find_chunk(ptr, end, fourcc("data"));
    if (!ptr)
        return nullptr;

    const uint8_t *wave_buffer = read_subchunk(wave_data, ptr);

    int32_t wave_buffer_size = wave_data.sub_chunk_size;
    if (wave_buffer_size > (end - wave_buffer))
        return nullptr;
    
    /* \todo throwing or error return question still applies here */
    if (wave_format.audio_format != WAVE_FORMAT_PCM)
    {
        printf("aeon::audio::codec_wav, invalid wav format, only supporting PCM wav\n");
        return nullptr;
    }

    sample_ptr result = std::make_unique<sample>(
        wave_format.num_channels,
        wave_format.bits_per_sample,
        wave_format.sample_rate,
        wave_buffer,
        wave_buffer_size);

    return result;
}

void codec_wav::seek(double /*position*/)
{

}

} // namespace audio
} // namespace aeon