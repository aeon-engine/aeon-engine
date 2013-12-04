#include "Aeon.h"
#include "AeonBuffer.h"
#include "AeonConsole.h"

namespace Aeon
{

Buffer::Buffer()
:
m_buffer(NULL),
m_size(0),
m_reserved_size(0),
m_disable_free(false)
{}

Buffer::Buffer(size_t size)
:
m_buffer(NULL),
m_size(0),
m_reserved_size(0),
m_disable_free(false)
{
	reserve(size);
}

Buffer::~Buffer()
{
	if (!m_disable_free)
		free();
}

bool Buffer::reserve(size_t n)
{
	//Do we already have this many bytes reserved?
	if(n <= m_reserved_size)
		return true;

	//Resize the array if we're requesting more bytes
	bool result = resize(n);

	if(result)
		Console::debug("Buffer: Reserved %u bytes at %x.", n, m_buffer);

	return result;
}

bool Buffer::resize(size_t n)
{
	//Reallocate the buffer to be the new size
	void *new_buffer = realloc(m_buffer, n);

	//Did we fail to reallocate our buffer?
	if(new_buffer == NULL)
	{
		//Do we have data at all?
		if(m_buffer != NULL)
		{
			Console::warning("Buffer: Failed to reallocate buffer from %u to %u at %x. Trying copy.", m_reserved_size, n, m_buffer);

			//Try a fallback method...
			new_buffer = malloc(n);

			//Did we fail again?!
			if (new_buffer == NULL)
			{
				Console::fatal("Buffer: Failed to reallocate buffer from %u to %u at %x in fallback mode. Aborting", m_reserved_size, n, m_buffer);
				return false;
			}

			//How many bytes do we need to copy? Are we increasing or shrinking?
			size_t newsize = (n < m_reserved_size) ? n : m_reserved_size;

			//All ok! Lets copy!
			memcpy(new_buffer, m_buffer, newsize);

			//Free the old buffer
			::free(m_buffer);

			m_buffer = new_buffer;

			return true;
		}

		Console::fatal("Buffer: Could not allocate buffer for %u bytes.", n);
		return false;
	}

	//All is ok! Let's keep our new data
	m_buffer = new_buffer;
	m_reserved_size = n;

	return true;
}

bool Buffer::append(void *data, size_t len)
{
	//Does our appended data fit?
	if(m_size + len > m_reserved_size)
	{
		//Make sure our buffer is able to fit this data
		if(!reserve(m_reserved_size + len))
			return false;
	}

	char *buff = (char *) m_buffer;
	memcpy(&buff[m_size], data, len);

	m_size += len;

	return true;
}

void Buffer::free()
{
	if(m_buffer)
		::free(m_buffer);

	Console::debug("Buffer: Freed %u bytes at %x.", m_size, m_buffer);

	m_buffer = NULL;
	m_size = 0;
	m_reserved_size = 0;
}

void Buffer::disable_free_on_destruct()
{
	m_disable_free = true;
}

} //namespace Aeon
