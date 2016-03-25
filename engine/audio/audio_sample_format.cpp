#include <audio/audio_sample_format.h>

constexpr
uint32_t fourcc(char const p[5])
{
    return (p[3] << 24) | (p[2] << 16) | (p[1] << 8) | p[0];
}

namespace aeon
{
namespace audio
{
sample_format format_by_file_extention(std::string filename)
{
    std::string file_extention = filename.substr(filename.size() - 4, 4);
    if (file_extention == ".wav")
        return sample_format::wav;
    else if (file_extention == ".ogg")
        return sample_format::ogg;

    // always default to wav... as a error there is tracked easier
    return sample_format::wav;
}

aeon::audio::sample_format format_by_fourcc(uint32_t fourcc_value)
{
    if (fourcc_value == fourcc("OggS"))
        return sample_format::ogg;
    else
        return sample_format::wav;
}

} // namespace audio
} // namespace aeon

