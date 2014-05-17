#include "Aeon/Aeon.h"
#include "Aeon/Console/StreamListener.h"
#include "Aeon/Utility/StringUtils.h"

namespace Aeon
{

ConsoleStreamListener::ConsoleStreamListener(StreamPtr stream)
:
stream_(stream)
{

}


ConsoleStreamListener::~ConsoleStreamListener()
{

}

void ConsoleStreamListener::on_log_message(double time_diff, Console::LogLevel level, const std::string &message)
{
	if(!stream_)
		return;
	
	std::string time_string = Aeon::StringUtils::float_to_string((float) time_diff, 10) + ' ';
	stream_->write(time_string);

	switch(level)
	{
		case Console::LogLevel::Error:
		{
			stream_->write("[ERR] ");
		}break;
		case Console::LogLevel::Warning:
		{
			stream_->write("[WRN] ");
		}break;
		case Console::LogLevel::Info: //Info displays nothing.
		{
			stream_->write("[INF] ");
		}break;
		case Console::LogLevel::Debug:
		{
			stream_->write("[DBG] ");
		}break;
	}

	stream_->write(message);
	stream_->write("\n");
}

} /* namespace Aeon */
