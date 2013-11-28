#ifndef AeonConsole_h__
#define AeonConsole_h__

namespace Aeon
{

class ConsoleListener;
typedef std::set<ConsoleListener *> ConsoleListeners;
class Console
{
public:
	enum class LogLevel : int
	{
		FATAL		= 1,
		ERROR		= 2,
		WARNING		= 3,
		INFO		= 4,
		DEBUG		= 99
	};

	Console();
	~Console();

	void					log(LogLevel level, const char *format, ...);

	void					set_loglevel(LogLevel level)	{ m_loglevel = level; }
	LogLevel				get_loglevel()					{ return m_loglevel; }

	void					add_console_listener(ConsoleListener *listener);
	void					remove_console_listener(ConsoleListener *listener);

private:
	LogLevel				m_loglevel;
	ConsoleListeners		m_console_listeners;

	static char 			m_console_output_buffer[AEON_CONSOLE_BUFFER_SIZE];
};

} //namespace Aeon

#endif // AeonConsole_h__
