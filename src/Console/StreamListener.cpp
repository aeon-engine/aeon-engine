#include "Aeon/Aeon.h"
#include "Aeon/Console/StreamListener.h"
#include "Aeon/Utility/StringUtils.h"

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

void ConsoleStreamListener::on_log_message(double time_diff, Console::LogLevel level, const std::string &message)
{
	if(!m_stream)
		return;
	
	std::string time_string = Aeon::StringUtils::float_to_string((float) time_diff, 10) + ' ';
	m_stream->write(time_string);

	switch(level)
	{
		case Console::LogLevel::Fatal:
		{
			m_stream->write("[FATAL]  ");
		}break;
		case Console::LogLevel::Error:
		{
			m_stream->write("[ERROR]  ");
		}break;
		case Console::LogLevel::Warning:
		{
			m_stream->write("[WARNING]");
		}break;
		case Console::LogLevel::Info: //Info displays nothing.
		{
			m_stream->write("[INFO]   ");
		}break;
		case Console::LogLevel::Debug:
		{
			m_stream->write("[DEBUG]  ");
		}break;
	}

	m_stream->write(message);
	m_stream->write("\n");
}

} //namespace Aeon
