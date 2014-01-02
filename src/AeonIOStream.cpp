#include "Aeon.h"
#include "AeonIOStream.h"
#include "AeonConsole.h"

namespace Aeon
{

IOStream::IOStream(int access_mode /*= AccessMode::READ*/)
:
Stream(access_mode)
{

}

IOStream::IOStream(const std::string &name, int access_mode /*= AccessMode::READ*/)
:
Stream(name, access_mode)
{

}

size_t IOStream::read(void *buffer, size_t count)
{
	if (!(m_access_mode & AccessMode::READ))
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

size_t IOStream::write(const void *buffer, size_t count)
{
	if (m_access_mode != AccessMode::WRITE)
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

size_t IOStream::read_line(std::string &str)
{
	if (m_access_mode != AccessMode::READ)
	{
		Console::error("IOStream: Read on write-only stream.");
		return 0;
	}

	//AEON_FILE_LINE_BUFFER_SIZE
	std::string line;

	for (int i = 0; i < AEON_STREAM_MAX_TEXT_LINE_LENGTH; ++i)
	{
		int c = fgetc(stdin);

		if (c == EOF)
			break;

		if (c == '\n')
			break;

		line += (char) c;
	}

	str = line;

	return line.length();
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
