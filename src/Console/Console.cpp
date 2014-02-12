#include "Aeon.h"
#include "AeonConsoleListener.h"

namespace Aeon
{
namespace Console
{

static LogLevel				m_loglevel = AEON_DEFAULT_CONSOLE_LOG_LEVEL;
static ConsoleListeners		m_console_listeners;
static char 				m_console_output_buffer[AEON_CONSOLE_BUFFER_SIZE];

static void log(LogLevel level, const char *format, va_list args)
{
	//Only log messages from our current log level and higher importance
	if (level > m_loglevel)
		return;

	//Format the message
	vsnprintf(m_console_output_buffer, AEON_CONSOLE_BUFFER_SIZE, format, args);

	//Notify all console listeners
	for (auto itr : m_console_listeners)
	{
		itr->on_log_message(level, m_console_output_buffer);
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
	m_loglevel = level;
}

LogLevel get_loglevel()
{
	return m_loglevel;
}

void add_console_listener(ConsoleListenerPtr listener)
{
	m_console_listeners.insert(listener);
}

void remove_console_listener(ConsoleListenerPtr listener)
{
	m_console_listeners.erase(listener);
}

void remove_all_console_listeners()
{
	m_console_listeners.clear();
}

} //namespace Console
} //namespace Aeon
