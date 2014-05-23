#ifndef AeonResourceManager_h__
#define AeonResourceManager_h__

#include "Aeon/Resources/Resource.h"
#include "Aeon/Streams/Stream.h"

namespace aeon
{

class resource_manager
{
friend class resource;
public:
	typedef std::map<std::string, resource_ptr> ResourceMap;
	typedef std::queue<resource_ptr> ResourceQueue;

	resource_manager();
	virtual ~resource_manager();

	resource_ptr				load(stream_ptr stream);
	resource_ptr				load(const std::string &name);

	bool					unload(resource_ptr resource);
	bool					unload(const std::string &name);

	int						finalize_resources();

protected:
	bool					__is_name_unique(const std::string &name);
	resource_ptr				__load(stream_ptr stream);

	virtual resource *		__create_new_resource(const std::string &name) = 0;

	void					__mark_as_finalize(resource_ptr resource);
	
	ResourceMap				resource_map_;
	std::mutex				resource_map_mutex_;

	ResourceQueue			resource_queue_;
	std::mutex				resource_queue_mutex_;
};

} /* namespace Aeon */

#endif /* AeonResourceManager_h__ */
