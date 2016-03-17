#include <audio/source_manager.h>

namespace aeon
{
namespace audio 
{

source_manager::source_manager()
{
    initialize(1024); // just fake the source hint nr for now
}

source_manager::~source_manager()
{

}

void source_manager::initialize(int nr_sources_hint)
{
    max_nr_sources_ = __detect_nr_of_voices(nr_sources_hint);
    nr_available_sources_ = max_nr_sources_;

    for (int i = 0; i < nr_available_sources_; ++i)
        sources_.push_back(std::make_shared<aeon::audio::source>());

    // make a copy of sources...
    for (auto itr : sources_)
        free_sources_.push(itr);
}


int source_manager::__detect_nr_of_voices(int nr_sources_hint)
{
    std::vector<ALuint> temp_source;
    temp_source.resize(nr_sources_hint);

    int i = 0;
    for (; i < nr_sources_hint; ++i)
    {
        alGenSources(1, &temp_source[i]);

        // if the generation of the audio source failed we have reached our
        // limit
        if (alGetError() != AL_NO_ERROR)
            break;
    }

    // if we failed to generate any sources to begin with, just return.
    if (i == 0)
    {
        printf("aeon::audio::source_manager failed to detected voice count\n");
        return 0;
    }

    alDeleteSources(i, temp_source.data());

    printf("aeon::audio::source_manager detected voice count: %d\n", i);
    return i;
}

aeon::audio::source_ptr source_manager::get_source()
{
    auto source = free_sources_.front();
    free_sources_.pop();

    taken_sources_.push_back(source);

    return source;
}

} // namespace audio
} // namespace aeon