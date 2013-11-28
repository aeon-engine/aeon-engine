#include "Aeon.h"
#include "AeonConsole.h"
#include "AeonConsoleListener.h"

namespace Aeon
{

char Console::m_console_output_buffer[AEON_CONSOLE_BUFFER_SIZE];

Console::Console()
:
m_loglevel(AEON_DEFAULT_CONSOLE_LOG_LEVEL)
{

}

Console::~Console()
{
	//Clean up all console listeners
	for (ConsoleListeners::iterator itr = m_console_listeners.begin(); itr != m_console_listeners.end(); ++itr)
	{
		ConsoleListener *listener = (ConsoleListener *) *itr;
		delete listener;
	}

	m_console_listeners.clear();
}

void Console::log(LogLevel level, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	//Format the message
	vsnprintf(m_console_output_buffer, AEON_CONSOLE_BUFFER_SIZE, format, args);

	//Only log messages from our current log level and higher importance
	if (level > m_loglevel)
		return;

	//Notify all console listeners
	for (ConsoleListeners::iterator itr = m_console_listeners.begin(); itr != m_console_listeners.end(); ++itr)
	{
		ConsoleListener *listener = (ConsoleListener *)*itr;
		listener->on_log_message(level, m_console_output_buffer);
	}

	va_end(args);
}

void Console::add_console_listener(ConsoleListener *listener)
{
	m_console_listeners.insert(listener);
}

void Console::remove_console_listener(ConsoleListener *listener)
{
	m_console_listeners.erase(listener);
}

} //namespace Aeon
