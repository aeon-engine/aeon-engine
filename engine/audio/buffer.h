#pragma once

#include <audio/buffer_interface.h>
#include <audio/openal/openal_includes.h>

#include <string>
#include <memory>
#include <vector>

namespace aeon
{
namespace audio
{

/* this is a static buffer, used for frequently used short samples */
class buffer : public ibuffer
{
public:
    buffer();
    ~buffer();

    void load(std::string filename, sample_format format = sample_format::auto_detect) override;
    void bind_source(aeon::audio::source *source) override;
    void unbind_source(aeon::audio::source *source) override;
    void prepare() override;

//private:
    ALuint buffer_;
private:
    std::vector<aeon::audio::source *> sources_;
};

using buffer_ptr = std::shared_ptr<buffer>;

} // namespace audio
} // namespace aeon
