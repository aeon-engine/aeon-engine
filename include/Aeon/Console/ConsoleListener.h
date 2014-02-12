#ifndef AeonConsoleListener_h__
#define AeonConsoleListener_h__

#include "Aeon/Console/Console.h"

namespace Aeon
{

class ConsoleListener
{
public:
	ConsoleListener() {}
	virtual ~ConsoleListener() {}

	virtual void on_log_message(Console::LogLevel level, const std::string &message) = 0;
};

typedef std::shared_ptr<ConsoleListener> ConsoleListenerPtr;

} //namespace Aeon

#endif // AeonConsoleListener_h__
