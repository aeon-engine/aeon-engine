#ifndef AeonResourceManager_h__
#define AeonResourceManager_h__

#include "Aeon/Resources/Resource.h"
#include "Aeon/Streams/Stream.h"

namespace Aeon
{

class ResourceManager
{
friend class Resource;
public:
	typedef std::map<std::string, ResourcePtr> ResourceMap;
	typedef std::queue<ResourcePtr> ResourceQueue;

	ResourceManager();
	virtual ~ResourceManager();

	ResourcePtr				load(StreamPtr stream);
	ResourcePtr				load(const std::string &name);

	bool					unload(ResourcePtr resource);
	bool					unload(const std::string &name);

	int						finalize_resources();

protected:
	bool					__is_name_unique(const std::string &name);
	ResourcePtr				__load(StreamPtr stream);

	virtual Resource *		__create_new_resource(const std::string &name) = 0;

	void					__mark_as_finalize(ResourcePtr resource);
	
	ResourceMap				resource_map_;
	std::mutex				resource_map_mutex_;

	ResourceQueue			resource_queue_;
	std::mutex				resource_queue_mutex_;
};

} /* namespace Aeon */

#endif /* AeonResourceManager_h__ */
