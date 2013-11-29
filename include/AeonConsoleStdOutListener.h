#ifndef AeonConsoleStdOutListener_h__
#define AeonConsoleStdOutListener_h__

#include "AeonConsoleListener.h"

namespace Aeon
{

class ConsoleStdOutListener : public ConsoleListener
{
public:
	ConsoleStdOutListener() {}
	~ConsoleStdOutListener() {}

	void on_log_message(Console::LogLevel level, const char *message);
};

} //namespace Aeon

#endif // AeonConsoleStdOutListener_h__
