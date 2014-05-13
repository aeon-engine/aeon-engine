#include "Aeon/Aeon.h"
#include "Aeon/Console/ConsoleListener.h"
#include "Aeon/Utility/Timer.h"

namespace Aeon
{
namespace Console
{

static LogLevel				loglevel_ = AEON_DEFAULT_CONSOLE_LOG_LEVEL;
static ConsoleListeners		console_listeners_;
static char 				console_output_buffer_[AEON_CONSOLE_BUFFER_SIZE];
static Aeon::Timer			diff_timer_;
static std::mutex			console_mutex_;

static void log(LogLevel level, const char *format, va_list args)
{
	std::lock_guard<std::mutex> lock(console_mutex_);

	//Only log messages from our current log level and higher importance
	if (level > loglevel_)
		return;

	//Format the message
	vsnprintf(console_output_buffer_, AEON_CONSOLE_BUFFER_SIZE, format, args);

	//Notify all console listeners
	for (auto itr : console_listeners_)
	{
		itr->on_log_message(diff_timer_.get_time_difference(), level, console_output_buffer_);
	}
}

void fatal(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	log(LogLevel::Fatal, format, args);
	va_end(args);
}

void error(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	log(LogLevel::Error, format, args);
	va_end(args);
}

void warning(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	log(LogLevel::Warning, format, args);
	va_end(args);
}

void info(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	log(LogLevel::Info, format, args);
	va_end(args);
}

void debug(const char *format, ...)
{
#ifdef AEON_CONSOLE_OUTPUT_DEBUG_MSGS
	va_list args;
	va_start(args, format);
	log(LogLevel::Debug, format, args);
	va_end(args);
#endif
}

void set_loglevel(LogLevel level)
{
	std::lock_guard<std::mutex> lock(console_mutex_);
	loglevel_ = level;
}

LogLevel get_loglevel()
{
	std::lock_guard<std::mutex> lock(console_mutex_);
	LogLevel level = loglevel_;

	return level;
}

void add_console_listener(ConsoleListenerPtr listener)
{
	std::lock_guard<std::mutex> lock(console_mutex_);
	console_listeners_.insert(listener);
}

void remove_console_listener(ConsoleListenerPtr listener)
{
	std::lock_guard<std::mutex> lock(console_mutex_);
	console_listeners_.erase(listener);
}

void remove_all_console_listeners()
{
	std::lock_guard<std::mutex> lock(console_mutex_);
	console_listeners_.clear();
}

} //namespace Console
} //namespace Aeon
