#ifndef AeonResourceManager_h__
#define AeonResourceManager_h__

#include "Aeon/Resources/Resource.h"

namespace Aeon
{

class ResourceManager
{
public:
	typedef std::map<std::string, ResourcePtr> ResourceMap;
	typedef std::map<Resource::Handle, ResourcePtr> ResourceHandleMap;

	ResourceManager();
	virtual ~ResourceManager();

protected:
	ResourcePtr __create_or_retrieve(const std::string &name, Resource::Handle handle);

	virtual Resource * __create_internal(const std::string &name, Resource::Handle handle) = 0;

};

} /* namespace Aeon */

#endif /* AeonResourceManager_h__ */
