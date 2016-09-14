#include <audio/openal/openal_format.h>

ALenum get_openal_format(int channel_count, int bits_per_sample)
{
    if (channel_count == 2) // stereo
    {
        if (bits_per_sample == 8)
        {
            return AL_FORMAT_STEREO8;
        }
        else if (bits_per_sample == 16)
        {
            return AL_FORMAT_STEREO16;
        }
        else
        {
            // we only support 8 and 16 bit wav's for now.
            printf("aeon::audio::buffer, unsupported bits per sample\n");
            return 0;
        }
    }
    else if (channel_count == 1) // mono
    {
        if (bits_per_sample == 8)
        {
            return AL_FORMAT_MONO8;
        }
        else if (bits_per_sample == 16)
        {
            return AL_FORMAT_MONO16;
        }
        else
        {
            // we only support 8 and 16 bit wav's for now.
            printf("aeon::audio::buffer, unsupported bits per sample\n");
            return 0;
        }
    }
    else
    {
        // we only support mono and stereo for now
        printf("aeon::audio::buffer, unsupported channel count\n");
        return 0;
    }
}

ALenum get_openal_format(const aeon::audio::sample_buffer_ptr &sample)
{
    return get_openal_format(sample->channel_count_, sample->bits_per_sample_);
}