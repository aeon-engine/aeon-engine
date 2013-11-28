#include "Aeon.h"
#include "AeonConsoleStdOutListener.h"

namespace Aeon
{

void ConsoleStdOutListener::on_log_message(Console::LogLevel level, const char *message)
{
	switch(level)
	{
		case Console::LogLevel::FATAL:
		{
			printf("[ FATAL ] ");
		}break;
		case Console::LogLevel::ERROR:
		{
			printf("[ ERROR ] ");
		}break;
		case Console::LogLevel::WARNING:
		{
			printf("[WARNING] ");
		}break;
		case Console::LogLevel::INFO: //Info displays nothing.
		{
		}break;
		case Console::LogLevel::DEBUG:
		{
			printf("[ DEBUG ] ");
		}break;
	}

	puts(message);
}

} //namespace Aeon