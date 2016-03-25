#pragma once

#include <string>

namespace aeon
{
namespace audio
{
enum class sample_format
{
    auto_detect,
    wav, // only supporting plain PCM
    ogg, // actually its vorbis
    opus,
};

/*! \note this is hacky... I know... */
sample_format format_by_file_extention(std::string filename);
sample_format format_by_fourcc(uint32_t fourcc_value);

} // namespace audio
} // namespace aeon