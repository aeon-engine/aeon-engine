#include "Aeon/Aeon.h"
#include "Aeon/Resources/Resource.h"

namespace Aeon
{

Resource::Resource(ResourceManager *creator, const std::string &name, Handle handle)
:
creator_(creator),
name_(name),
handle_(handle)
{

}

Resource::~Resource()
{

}

} /* namespace Aeon */
