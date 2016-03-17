#pragma once

#include <audio/source.h>
#include <audio/openal/openal_includes.h>

#include <vector>
#include <thread>
#include <mutex>
#include <queue>

namespace aeon
{
namespace audio
{

// manager class per device, which also runs a thread pool to fill the channels
class source_manager
{
public:
    source_manager();
    ~source_manager();

    /*!
     * \param[in] nr_sources_hint is a number supplied by the driver that tells
     *            us how many sources are available.
     */
    void initialize(int nr_sources_hint);

    int __detect_nr_of_voices(int nr_sources_hint);

    source_ptr get_source();

    int max_nr_sources_;
    int nr_available_sources_;
    std::thread update_thread_; // \todo implement update thread :P
    std::mutex stream_list_lock_;
    
    // note this free/taken design is crap...!!!
    std::vector<source_ptr> sources_; //all sources
    std::queue<source_ptr> free_sources_; // free sources
    std::vector<source_ptr> taken_sources_; // sources that are currently active
};

} // namespace audio
} // namespace aeon
