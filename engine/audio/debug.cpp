#include <audio/debug.h>
#include <audio/sample.h>
#include <audio/openal/openal_includes.h>
#include <audio/openal/openal_check.h>
#include <audio/openal/openal_format.h>

const char *get_openal_format_name(ALenum format)
{
    switch (format)
    {
    case AL_FORMAT_STEREO8: return "AL_FORMAT_STEREO8"; break;
    case AL_FORMAT_STEREO16: return "AL_FORMAT_STEREO16"; break;
    case AL_FORMAT_MONO8: return "AL_FORMAT_MONO8"; break;
    case AL_FORMAT_MONO16: return "AL_FORMAT_MONO16"; break;
    }

    return "AL_FORMAT_UNKNOWN";
}

void dump_sample_stats(const aeon::audio::sample_ptr &sample)
{
    auto sample_format = get_openal_format(sample);

    printf("aeon::audio::buffer, sample stats:\n");
    printf("  channel nr  :  %d\n", sample->channel_count_);
    printf("  sample rate : %d\n", sample->sample_rate_);
    printf("  bps         : %d\n", sample->bits_per_sample_);
    printf("  openal:\n");
    printf("    format    : %s\n", get_openal_format_name(sample_format));
    printf("    sample nr : %I64u\n", sample->get_channel_sample_count());
}

void dump_al_buffer_stats(ALuint buffer)
{
    ALint size, bits, channels, frequency;
    al_check(alGetBufferi(buffer, AL_SIZE, &size));
    al_check(alGetBufferi(buffer, AL_BITS, &bits));
    al_check(alGetBufferi(buffer, AL_CHANNELS, &channels));
    al_check(alGetBufferi(buffer, AL_FREQUENCY, &frequency));

    printf("aeon::audio::buffer openal buffer stats:\n");
    printf("  size: %d\n", size);
    printf("  bits: %d\n", bits);
    printf("  channels: %d\n", channels);
    printf("  frequency: %d\n", frequency);
}

ALint get_samples_processed(ALuint buffer)
{
    ALint size, bits, channels;
    al_check(alGetBufferi(buffer, AL_SIZE, &size));
    al_check(alGetBufferi(buffer, AL_BITS, &bits));
    al_check(alGetBufferi(buffer, AL_CHANNELS, &channels));
    return channels * (size / (bits / 8));
}

/*double get_sample_time(aeon::audio::sample_ptr &sample)
{
    double sample_count = (double)get_sample_count(sample);
    return double(sample_count) / double(sample->sample_rate_);
}
*/
