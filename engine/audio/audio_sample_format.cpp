#include <audio/audio_sample_format.h>

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

} // namespace audio
} // namespace aeon

