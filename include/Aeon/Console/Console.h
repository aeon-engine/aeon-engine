#ifndef AeonConsole_h__
#define AeonConsole_h__

namespace Aeon
{

class ConsoleListener;
typedef std::shared_ptr<ConsoleListener> ConsoleListenerPtr;

namespace Console
{

typedef std::set<ConsoleListenerPtr> ConsoleListeners;

enum class LogLevel : int
{
	Error		= 1,
	Warning		= 2,
	Info		= 3,
	Debug		= 99
};

void					error(const char *format, ...);
void					warning(const char *format, ...);
void					info(const char *format, ...);
void					debug(const char *format, ...);

void					set_loglevel(LogLevel level);
LogLevel				get_loglevel();

void					add_console_listener(ConsoleListenerPtr listener);
void					remove_console_listener(ConsoleListenerPtr listener);
void					remove_all_console_listeners();

} //namespace Console
} //namespace Aeon

#endif // AeonConsole_h__
