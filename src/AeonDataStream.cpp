#include "Aeon.h"
#include "AeonDataStream.h"

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
}

} //namespace Aeon
