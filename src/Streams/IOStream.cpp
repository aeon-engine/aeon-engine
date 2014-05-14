#include "Aeon/Aeon.h"
#include "Aeon/Streams/IOStream.h"
#include "Aeon/Console/Console.h"

namespace Aeon
{

IOStream::IOStream(int access_mode /*= AccessMode::Read*/)
:
Stream(access_mode)
{

}

IOStream::IOStream(const std::string &name, int access_mode /*= AccessMode::Read*/)
:
Stream(name, access_mode)
{

}

size_t IOStream::read(void *buffer, size_t count)
{
	if (!(access_mode_ & AccessMode::Read))
	{
		Console::error("IOStream: Read on write-only stream.");
		return 0;
	}

	if (!buffer)
	{
		Console::error("IOStream: Input buffer is NULL.");
		return 0;
	}

	if (count == 0)
	{
		Console::warning("IOStream: Tried writing 0 bytes.");
		return 0;
	}

	return fread(buffer, 1, count, stdin);
}

bool IOStream::read(std::uint8_t &data)
{
	if (!(access_mode_ & AccessMode::Read))
	{
		Console::error("IOStream: Read on write-only stream.");
		return false;
	}

	int c = fgetc(stdin);

	if (c == EOF)
		return false;

	data = (std::uint8_t) c;
	return true;
}

bool IOStream::peek(std::uint8_t &data)
{
	if (!(access_mode_ & AccessMode::Read))
	{
		Console::error("IOStream: Peek on write-only stream.");
		return false;
	}

	int c = fgetc(stdin);

	if (c == EOF)
		return false;

	//TODO: research if there is a good alternative for this.
	if (ungetc(c, stdin) == EOF)
		return false;

	data = (std::uint8_t) c;
	return true;
}

size_t IOStream::write(const void *buffer, size_t count)
{
	if (access_mode_ != AccessMode::Write)
	{
		Console::error("IOStream: Write on read-only stream.");
		return 0;
	}

	if (!buffer)
	{
		Console::error("IOStream: Input buffer is NULL.");
		return 0;
	}

	if (count == 0)
	{
		Console::warning("IOStream: Tried writing 0 bytes.");
		return 0;
	}

	return fwrite(buffer, 1, count, stdout);
}

bool IOStream::seek(size_t pos, SeekDirection direction)
{
	AEON_UNUSED(pos);
	AEON_UNUSED(direction);

	//This won't work for STDIN...
	return false;
}

size_t IOStream::tell() const
{
	//This won't work for STDIN...
	return 0;
}

bool IOStream::eof() const
{
	return (feof(stdin) != 0);
}

void IOStream::flush()
{
	fflush(stdout);
}

Aeon::BufferPtr IOStream::get_as_buffer()
{
	//This won't work for STDIN...
	return AeonEmptyBuffer;
}

} //namespace Aeon
