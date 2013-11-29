#include "Aeon.h"
#include "AeonBuffer.h"
#include "AeonConsole.h"

namespace Aeon
{

Buffer::Buffer()
:
m_buffer(NULL),
m_size(0)
{}

Buffer::Buffer(long size)
:
m_buffer(NULL),
m_size(0)
{
	alloc(size);
}

Buffer::~Buffer()
{
	free();
}

void Buffer::alloc(long size)
{
	//First free the buffer if there was anything in it.
	if(m_buffer != NULL || m_size > 0)
		free();

	m_buffer = (unsigned char *)malloc(size);
	m_size = size;

	Console::debug("Buffer: Allocated %u bytes at %x.", size, m_buffer);
}

void Buffer::free()
{
	if (m_buffer)
		::free(m_buffer);

	Console::debug("Buffer: Freed %u bytes at %x.", m_size, m_buffer);

	m_buffer = NULL;
	m_size = 0;
}



} //namespace Aeon
