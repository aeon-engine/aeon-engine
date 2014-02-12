#include "Aeon.h"
#include "AeonResource.h"

namespace Aeon
{

Resource::Resource(ResourceManager *creator, const std::string &name, Handle handle)
:
m_creator(creator),
m_name(name),
m_handle(handle)
{

}

Resource::~Resource()
{

}

} //namespace Aeon
