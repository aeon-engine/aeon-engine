#pragma once

#include <audio/audio_buffer.h>
#include <audio/openal/openal_includes.h>

#include <string>
#include <memory>
#include <vector>
#include <list>

namespace aeon
{
namespace audio
{

/* this is a static buffer, used for frequently used short samples */
class buffer_static : public buffer
{
public:
    buffer_static();
    virtual ~buffer_static() override;

    void load(std::string filename, sample_format format = sample_format::auto_detect) override;
    void load(common::buffer_u8 &data, sample_format format = sample_format::auto_detect) override;
    void bind_source(aeon::audio::source *source) override;
    void unbind_source(aeon::audio::source *source) override;
    void prepare() override;

    // private:
    ALuint buffer_;

private:
    std::list<aeon::audio::source *> sources_;
};

using buffer_static_ptr = std::shared_ptr<buffer_static>;

} // namespace audio
} // namespace aeon
