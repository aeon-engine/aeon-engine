#ifndef AeonResourceManager_h__
#define AeonResourceManager_h__

#include "Aeon/Resources/Resource.h"
#include "Aeon/Streams/Stream.h"

namespace Aeon
{

class ResourceManager
{
public:
	typedef std::map<std::string, ResourceWeakPtr> ResourceMap;

	ResourceManager();
	virtual ~ResourceManager();

	ResourcePtr				load(StreamPtr stream);
	ResourcePtr				load(const std::string &name);

protected:
	bool					__is_name_unique(const std::string &name);
	ResourcePtr				__load(StreamPtr stream);

	virtual Resource *		__create_new_resource(const std::string &name) = 0;

private:
	ResourceMap				resources_;
};

} /* namespace Aeon */

#endif /* AeonResourceManager_h__ */
