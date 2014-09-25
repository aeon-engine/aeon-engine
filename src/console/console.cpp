#include "aeon/aeon.h"
#include "aeon/console/consolelistener.h"
#include "aeon/utility/timer.h"

namespace aeon
{
namespace console
{

static log_level           loglevel_ = AEON_DEFAULT_CONSOLE_LOG_LEVEL;
static console_listeners   console_listeners_;
static char                console_output_buffer_[AEON_CONSOLE_BUFFER_SIZE];
static aeon::timer         diff_timer_;
static std::mutex          console_mutex_;

static void log(log_level level, const char *format, va_list args)
{
    std::lock_guard<std::mutex> lock(console_mutex_);

    //Only log messages from our current log level and higher importance
    if(level > loglevel_)
        return;

    //Format the message
    vsnprintf(console_output_buffer_, AEON_CONSOLE_BUFFER_SIZE, format, args);

    //Notify all console listeners
    for(auto itr : console_listeners_)
    {
        itr->on_log_message(diff_timer_.get_time_difference(), level, 
            console_output_buffer_);
    }
}

void error(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    log(log_level::error, format, args);
    va_end(args);
}

void warning(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    log(log_level::warning, format, args);
    va_end(args);
}

void info(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    log(log_level::info, format, args);
    va_end(args);
}

void debug(const char *format, ...)
{
#ifdef AEON_CONSOLE_OUTPUT_DEBUG_MSGS
    va_list args;
    va_start(args, format);
    log(log_level::debug, format, args);
    va_end(args);
#endif
}

void set_loglevel(log_level level)
{
    std::lock_guard<std::mutex> lock(console_mutex_);
    loglevel_ = level;
}

log_level get_loglevel()
{
    std::lock_guard<std::mutex> lock(console_mutex_);
    log_level level = loglevel_;

    return level;
}

void add_console_listener(console_listener_ptr listener)
{
    std::lock_guard<std::mutex> lock(console_mutex_);
    console_listeners_.insert(listener);
}

void remove_console_listener(console_listener_ptr listener)
{
    std::lock_guard<std::mutex> lock(console_mutex_);
    console_listeners_.erase(listener);
}

void remove_all_console_listeners()
{
    std::lock_guard<std::mutex> lock(console_mutex_);
    console_listeners_.clear();
}

} //namespace console
} //namespace aeon
