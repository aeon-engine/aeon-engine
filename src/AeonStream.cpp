#include "Aeon.h"
#include "AeonStream.h"

namespace Aeon
{

Stream::Stream(int access_mode /*= AccessMode::READ*/)
:
m_size(0),
m_access_mode(access_mode)
{}

Stream::Stream(const std::string &name, int access_mode /*= AccessMode::READ*/)
:
m_name(name),
m_size(0),
m_access_mode(access_mode)
{}

Stream::~Stream()
{
	close();
}

BufferPtr Stream::get_as_buffer()
{
	size_t s = size();
	
	BufferPtr buff(new Buffer(s));
	read(buff->get(), s);

	return buff;
}

size_t Stream::write(const std::string &str)
{
	return write(str.data(), str.size());
}

} //namespace Aeon
