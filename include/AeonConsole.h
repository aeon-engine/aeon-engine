#ifndef AeonConsole_h__
#define AeonConsole_h__

namespace Aeon
{

class ConsoleListener;

namespace Console
{

typedef std::set<ConsoleListener *> ConsoleListeners;

enum class LogLevel : int
{
	Fatal		= 1,
	Error		= 2,
	Warning		= 3,
	Info		= 4,
	Debug		= 99
};

void					fatal(const char *format, ...);
void					error(const char *format, ...);
void					warning(const char *format, ...);
void					info(const char *format, ...);
void					debug(const char *format, ...);

void					set_loglevel(LogLevel level);
LogLevel				get_loglevel();

void					add_console_listener(ConsoleListener *listener);
void					remove_console_listener(ConsoleListener *listener);
void					remove_all_console_listeners();
void					remove_and_delete_all_console_listeners();

} //namespace Console
} //namespace Aeon

#endif // AeonConsole_h__
