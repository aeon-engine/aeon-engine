#ifndef AeonConsoleStreamListener_h__
#define AeonConsoleStreamListener_h__

#include "AeonStream.h"
#include "AeonConsoleListener.h"

namespace Aeon
{

class ConsoleStreamListener : public ConsoleListener
{
public:
	ConsoleStreamListener(StreamPtr stream);
	~ConsoleStreamListener();

	void on_log_message(Console::LogLevel level, const std::string &message);

private:
	StreamPtr		m_stream;
};

} //namespace Aeon

#endif // AeonConsoleStreamListener_h__
