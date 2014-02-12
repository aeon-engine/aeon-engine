#include "Aeon/Aeon.h"
#include "Aeon/Streams/MemoryStream.h"
#include "Aeon/Console/Console.h"

namespace Aeon
{

MemoryStream::MemoryStream(DeleteMode delete_mode /*= DeleteMode::DeleteOnDestruct*/, int access_mode /*= AccessMode::READ_WRITE*/)
:
Stream(access_mode),
m_buffer(std::make_shared<Buffer>()),
m_buffer_offset(0)
{
	//Set the correct delete mode in our buffer
	m_buffer->set_delete_mode(delete_mode == DeleteMode::DeleteOnDestruct ? Buffer::DeleteMode::DeleteOnDestruct : Buffer::DeleteMode::None);
}

MemoryStream::MemoryStream(BufferPtr buffer, int access_mode /*= AccessMode::READ_WRITE*/)
:
Stream(access_mode),
m_buffer(buffer),
m_buffer_offset(0)
{

}

MemoryStream::MemoryStream(void *buffer, size_t size, DeleteMode delete_mode /*= DeleteMode::DeleteOnDestruct*/, int access_mode /*= AccessMode::READ_WRITE*/)
:
Stream(access_mode),
m_buffer(std::make_shared<Buffer>(buffer, size)),
m_buffer_offset(0)
{
	//Set the correct delete mode in our buffer
	m_buffer->set_delete_mode(delete_mode == DeleteMode::DeleteOnDestruct ? Buffer::DeleteMode::DeleteOnDestruct : Buffer::DeleteMode::None);
}

MemoryStream::~MemoryStream()
{

}

size_t MemoryStream::read(void *buffer, size_t count)
{
	if (!(m_access_mode & AccessMode::READ))
	{
		Console::error("MemoryStream: Read on write-only stream.");
		return 0;
	}

	char *data = (char *) m_buffer->get();

	if (!data)
	{
		Console::error("MemoryStream: Read on empty stream. Buffer was NULL.");
		return 0;
	}

	if(!buffer)
	{
		Console::error("MemoryStream: Input buffer is NULL.");
		return 0;
	}

	if(count == 0)
	{
		Console::warning("MemoryStream: Tried writing 0 bytes.");
		return 0;
	}

	//Only read what we have
	if (m_buffer->size() < m_buffer_offset + count)
		count = m_buffer->size() - m_buffer_offset;

	//Are we really out of bounds?
	if(count <= 0)
		return 0;

	//Copy our data
	memcpy(buffer, &data[m_buffer_offset], count);

	return count;
}

size_t MemoryStream::write(const void *buffer, size_t count)
{
	if (!(m_access_mode & AccessMode::WRITE))
	{
		Console::error("MemoryStream: WRITE on write-only stream.");
		return 0;
	}

	//Make sure we have enough space in the buffer
	if (!m_buffer->reserve(m_buffer_offset + count))
	{
		Console::error("MemoryStream: WRITE on stream failed. Could not reserve memory.");
		return 0;
	}

	//Get our data pointer
	char *data = (char *)m_buffer->get();
	
	//Copy our data
	memcpy(&data[m_buffer_offset], buffer, count);

	return count;
}

size_t MemoryStream::read_line(std::string &str)
{
	if (!(m_access_mode & AccessMode::READ))
	{
		Console::error("MemoryStream: Read on write-only stream.");
		return 0;
	}

	char *data = (char *)m_buffer->get();

	if (data == NULL)
	{
		Console::error("MemoryStream: Read on empty stream. Buffer was NULL.");
		return 0;
	}

	std::string line;
	size_t character_offset = 0;
	for (int i = 0; i < AEON_STREAM_MAX_TEXT_LINE_LENGTH; ++i)
	{
		//Can we still read a character?
		if (m_buffer_offset + character_offset >= m_buffer->size())
			break;

		char c = data[m_buffer_offset + character_offset];

		if (c == '\n')
			break;

		line += c;

		character_offset++;
	}

	str = line;

	return line.length();
}

bool MemoryStream::seek(size_t pos, SeekDirection direction)
{
	size_t new_pos = 0;
	switch(direction)
	{
		case SeekDirection::Begin:		{ new_pos = pos; } break;
		case SeekDirection::Current:	{ new_pos = m_buffer_offset + pos; } break;
		case SeekDirection::End:		{ new_pos = m_buffer->size() - pos; } break;
	};

	//Can't go higher then the size of our buffer...
	if (new_pos >= m_buffer->size())
		return false;

	//Set the new offset if all is good
	m_buffer_offset = new_pos;
	return true;
}

size_t MemoryStream::tell() const
{
	return m_buffer_offset;
}

bool MemoryStream::eof() const
{
	return m_buffer_offset >= m_buffer->size();
}

void MemoryStream::close()
{
	//Create a new buffer, and remove all references to the old one.
	//This may leak memory if DeleteOnDestruct was not set.
	m_buffer = std::make_shared<Buffer>();
}

void MemoryStream::flush()
{
	//Nothing to do here.
}

bool MemoryStream::good()
{
	//Do we have a buffer?
	if(!(m_buffer->get() != NULL))
		return false;

	//Are we still within bounds?
	if(m_buffer_offset >= m_buffer->size())
		return false;

	//All ok!
	return true;
}

BufferPtr MemoryStream::get_as_buffer()
{
	return m_buffer;
}

} //namespace Aeon
