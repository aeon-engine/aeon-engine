#include "Aeon/Aeon.h"
#include "Aeon/Streams/Stream.h"
#include "Aeon/Console/Console.h"

namespace Aeon
{

Stream::Stream(int access_mode /*= AccessMode::Read*/)
:
name_(AEON_STREAM_DEFAULT_NAME),
size_(0),
access_mode_(access_mode)
{}

Stream::Stream(const std::string &name, int access_mode /*= AccessMode::Read*/)
:
name_(name),
size_(0),
access_mode_(access_mode)
{}

Stream::~Stream()
{
	close();
}

BufferPtr Stream::get_as_buffer()
{
	size_t s = size();
	
	auto buffer = std::make_shared<Buffer>(s);
	read(buffer->get(), s);

	return buffer;
}

size_t Stream::write(const std::string &str)
{
	return write(str.data(), str.size());
}

size_t Stream::write(BufferPtr buffer)
{
	if(!buffer)
	{
		Console::error("Stream: Tried writing an empty buffer to a stream.");
		return 0;
	}

	return write(buffer->get(), buffer->size());
}

size_t Stream::read_line(std::string &str)
{
	if (!(access_mode_ & AccessMode::Read))
	{
		Console::error("Stream: Read on write-only stream.");
		return 0;
	}

	std::uint8_t c = 0;
	bool result = true;

	std::string line;
	for (int i = 0; i < AEON_STREAM_MAX_TEXT_LINE_LENGTH; ++i)
	{
		//Read a character
		result = read(c);

		//Could we read anything?
		if(!result)
			break;

		//Check if it's a line-ending character
		if (c == '\n')
		{
			//Peek if the next character is a '\r'
			result = peek(c);

			//If it's '\r', then we should seek 1 byte ahead
			if (result && c == '\r')
				seek(1, SeekDirection::Current);

			break;
		}

		//Check if it's a line-ending character
		if (c == '\r')
		{
			//Peek if the next character is a '\n'
			result = peek(c);

			//If it's '\n', then we should seek 1 byte ahead
			if (result && c == '\n')
				seek(1, SeekDirection::Current);

			break;
		}

		line += c;
	}

	str = line;

	return line.length();
}

} /* namespace Aeon */
