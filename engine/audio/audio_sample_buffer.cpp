#include <audio/audio_sample_buffer.h>
#include <cstring>

namespace aeon
{
namespace audio
{

sample_buffer::sample_buffer()
    : channel_count_(0)
    , bits_per_sample_(0)
    , sample_rate_(0)
{
}

sample_buffer::sample_buffer(int channel_count, int bits_per_sample, int sample_rate, const uint8_t *data,
                             size_t data_len)
    : channel_count_(channel_count)
    , bits_per_sample_(bits_per_sample)
    , sample_rate_(sample_rate)
{
    data_.resize(data_len);
    memcpy(data_.data(), data, data_.size());
}

sample_buffer::~sample_buffer()
{
}

double sample_buffer::get_total_time()
{
    double sample_count = (double)get_channel_sample_count();
    return double(sample_count) / double(sample_rate_);
}

uint64_t sample_buffer::get_channel_sample_count()
{
    int sample_count_div = 1;
    if (channel_count_ == 2) // stereo
    {
        if (bits_per_sample_ == 8)
            sample_count_div = 2;
        else if (bits_per_sample_ == 16)
            sample_count_div = 4;
        else
            printf("aeon::audio::sample, unsupported bits per sample count\n");
    }
    else if (channel_count_ == 1) // mono
    {
        if (bits_per_sample_ == 8)
            sample_count_div = 1;
        else if (bits_per_sample_ == 16)
            sample_count_div = 2;
        else
            printf("aeon::audio::sample, unsupported bits per sample count\n");
    }
    else
        printf("aeon::audio::sample, unsupported channel count\n");

    return data_.size() / sample_count_div;
}

} // namespace audio
} // namespace aeon
