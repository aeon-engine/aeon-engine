#include "Aeon.h"
#include "AeonConsoleStdOutListener.h"

namespace Aeon
{

void ConsoleStdOutListener::on_log_message(Console::LogLevel level, const std::string &message)
{
	switch(level)
	{
		case Console::LogLevel::Fatal:
		{
			printf("[ FATAL ] ");
		}break;
		case Console::LogLevel::Error:
		{
			printf("[ ERROR ] ");
		}break;
		case Console::LogLevel::Warning:
		{
			printf("[WARNING] ");
		}break;
		case Console::LogLevel::Info: //Info displays nothing.
		{
		}break;
		case Console::LogLevel::Debug:
		{
			printf("[ DEBUG ] ");
		}break;
	}

	puts(message.c_str());
}

} //namespace Aeon
