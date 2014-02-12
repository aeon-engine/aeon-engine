#include "Aeon/Aeon.h"
#include "Aeon/Console/StreamListener.h"

namespace Aeon
{

ConsoleStreamListener::ConsoleStreamListener(StreamPtr stream)
:
m_stream(stream)
{

}


ConsoleStreamListener::~ConsoleStreamListener()
{

}

void ConsoleStreamListener::on_log_message(Console::LogLevel level, const std::string &message)
{
	if(!m_stream)
		return;

	switch(level)
	{
		case Console::LogLevel::Fatal:
		{
			m_stream->write("[ FATAL ] ");
		}break;
		case Console::LogLevel::Error:
		{
			m_stream->write("[ ERROR ] ");
		}break;
		case Console::LogLevel::Warning:
		{
			m_stream->write("[WARNING] ");
		}break;
		case Console::LogLevel::Info: //Info displays nothing.
		{
		}break;
		case Console::LogLevel::Debug:
		{
			m_stream->write("[ DEBUG ] ");
		}break;
	}

	m_stream->write(message);
	m_stream->write("\n");
}

} //namespace Aeon
