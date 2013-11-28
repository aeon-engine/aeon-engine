#ifndef AeonConsoleListener_h__
#define AeonConsoleListener_h__

#include "AeonConsole.h"

namespace Aeon
{

class ConsoleListener
{
public:
	virtual void on_log_message(Console::LogLevel level, const char *message) = 0;
};

} //namespace Aeon

#endif // AeonConsoleListener_h__
