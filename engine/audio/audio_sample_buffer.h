#pragma once

#include <memory>
#include <vector>
#include <cstdint>

namespace aeon
{
namespace audio
{

// sample for now is a raw buffer that contains info about the audio
class sample_buffer
{
public:
    sample_buffer();
    sample_buffer(int channel_count, int bits_per_sample, int sample_rate, const uint8_t *data, size_t data_len);
    ~sample_buffer();

    double get_total_time();
    uint64_t get_channel_sample_count();

    int channel_count_;
    int sample_rate_; /* think in the likes of: 44.1khz */
    int bits_per_sample_;

    std::vector<uint8_t> data_; // the data of the sample....
};

using sample_buffer_ptr = std::unique_ptr<sample_buffer>;

} // namespace audio
} // namespace aeon
