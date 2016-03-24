#include <audio/buffer_static.h>
#include <audio/source.h>
#include <audio/codec/audio_codec_wav.h>
#include <audio/codec/audio_codec_vorbis.h>
#include <audio/openal/openal_check.h>
#include <audio/openal/openal_format.h>

namespace aeon
{
namespace audio
{

buffer_static::buffer_static()
{
    al_check(alGenBuffers(1, &buffer_));
}

buffer_static::~buffer_static()
{
    for (auto source : sources_)
        source->unbind();

    al_check(alDeleteBuffers(1, &buffer_));
}

void buffer_static::load(std::string filename, sample_format format /*= sample_format::auto_detect*/)
{
    if (format == sample_format::auto_detect)
        format = format_by_file_extention(filename);

    // do magic
    // do something related to formats
    aeon::audio::codec_ptr codec;
    if (format == sample_format::wav)
        codec = std::make_unique<aeon::audio::codec_wav>();
    else if (format == sample_format::ogg)
        codec = std::make_unique<aeon::audio::codec_vorbis>();
    else
        __debugbreak();

    aeon::audio::sample_buffer_ptr sample = codec->decode(filename);
    if (!sample)
    {
        printf("aeon::audio::buffer unable to decode: '%s'\n", filename.c_str());
        return;
    }

    ALenum buffer_format = get_openal_format(sample);
    al_check(alBufferData(buffer_, buffer_format, sample->data_.data(), (ALsizei)sample->data_.size(), sample->sample_rate_));
}

void buffer_static::bind_source(aeon::audio::source *source)
{
    sources_.push_back(source);

    printf("aeon::audio::source bind buffer: %u\n", buffer_);
    al_check(alSourcei(source->get_al_source(), AL_BUFFER, buffer_));
}

void buffer_static::unbind_source(aeon::audio::source *source)
{
    // unbind audio buffer
    al_check(alSourcei(source->get_al_source(), AL_BUFFER, 0));

    sources_.erase(
        std::remove_if(sources_.begin(), sources_.end(), [source](audio::source *x) {return x == source; }),
        sources_.end());
}

void buffer_static::prepare()
{
    // for a normal static buffer there is not much (yet) to be done.
}

} // namespace audio
} // namespace aeon
