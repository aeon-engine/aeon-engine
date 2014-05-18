#include "Aeon/Aeon.h"
#include "Aeon/Resources/Resource.h"

namespace Aeon
{

Resource::Resource(ResourceManager *creator, const std::string &name)
:
creator_(creator),
name_(name)
{

}

Resource::~Resource()
{

}

} /* namespace Aeon */
