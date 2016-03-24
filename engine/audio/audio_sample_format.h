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

} // namespace audio
} // namespace aeon