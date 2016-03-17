#pragma once

#include <audio/openal/openal_includes.h> // only for ALenum
#include <audio/sample.h> // only for aeon::audio::sample_ptr

ALenum get_openal_format(int channel_count, int bits_per_sample);
ALenum get_openal_format(const aeon::audio::sample_ptr &sample);
