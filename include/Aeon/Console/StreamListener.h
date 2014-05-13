#ifndef AeonConsoleStreamListener_h__
#define AeonConsoleStreamListener_h__

#include "Aeon/Streams/Stream.h"
#include "Aeon/Console/ConsoleListener.h"

#include <ctime>

namespace Aeon
{

class ConsoleStreamListener : public ConsoleListener
{
public:
	ConsoleStreamListener(StreamPtr stream);
	~ConsoleStreamListener();

	void on_log_message(double time_diff, Console::LogLevel level, const std::string &message);

private:
	StreamPtr		stream_;
};

} //namespace Aeon

#endif // AeonConsoleStreamListener_h__
