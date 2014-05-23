#include "aeon/aeon.h"
#include "aeon/resources/resourceManager.h"
#include "aeon/console/console.h"
#include "aeon/streams/filestream.h"

namespace aeon
{

resource_manager::resource_manager()
{
	console::debug("[ResourceManager]: created.");
}

resource_manager::~resource_manager()
{
	console::debug("[ResourceManager]: disposed.");
}

resource_ptr resource_manager::load(stream_ptr stream)
{
	if (!stream)
	{
		console::warning("[ResourceManager]: Could not load resource from stream. Stream was NULL.");
		return aeon_empty_resource;
	}

	if (!stream->has_name())
	{
		console::warning("[ResourceManager]: Could not load resource from stream. Name was not set.");
		return aeon_empty_resource;
	}

	console::debug("[ResourceManager]: Loading resource '%s' by stream.", stream->get_name().c_str());

	if (!__is_name_unique(stream->get_name()))
	{
		console::warning("[ResourceManager]: Could not load resource '%s' from stream. Name was not unique.", stream->get_name().c_str());
		return aeon_empty_resource;
	}

	return __load(stream);
}

resource_ptr resource_manager::load(const std::string &name)
{
	std::lock_guard<std::mutex> lock(resource_map_mutex_);

	console::debug("[ResourceManager]: Loading resource '%s' by name.", name.c_str());

	//Check if this resource was already loaded before.
	ResourceMap::iterator itr = resource_map_.find(name);

	if (itr != resource_map_.end())
	{
		resource_ptr resource_ptr = itr->second;

		if (resource_ptr)
		{
			console::debug("[ResourceManager]: Resource '%s' was already loaded.", name.c_str());
			return resource_ptr;
		}

		console::debug("[ResourceManager]: Resource '%s' no longer exists. Removing old reference and reloading.", name.c_str());
		resource_map_.erase(itr);
	}

	file_stream_ptr filestream = std::make_shared<file_stream>(name, stream::access_mode::read);

	if (!filestream)
	{
		console::warning("[ResourceManager]: Could not load resource '%s'. FileStream could not be made.", name.c_str());
		return aeon_empty_resource;
	}

	if (!filestream->good())
	{
		console::warning("[ResourceManager]: Could not load resource '%s'. FileStream was bad.", name.c_str());
		return aeon_empty_resource;
	}

	return __load(filestream);
}

bool resource_manager::unload(resource_ptr resource)
{
	std::lock_guard<std::mutex> lock(resource_map_mutex_);
	//resource_map_.find(resource_map_);
	return false;
}

bool resource_manager::unload(const std::string &name)
{
	return false;
}

int resource_manager::finalize_resources()
{
	std::lock_guard<std::mutex> lock(resource_queue_mutex_);
	
	int count = 0;
	while(!resource_queue_.empty())
	{
		resource_ptr resource = resource_queue_.front();
		if (resource->get_state() == resource::state::ready_for_finalize)
			resource->__finalize();
		else if (resource->get_state() == resource::state::unloading)
			resource->__unload();
		else
			console::warning("[ResourceManager]: Queued resource %s was not in finalize or unloading state.", resource->get_name().c_str());

		resource_queue_.pop();

		++count;
	}

	return count;
}

bool resource_manager::__is_name_unique(const std::string &name)
{
	std::lock_guard<std::mutex> lock(resource_map_mutex_);

	//If the result of find is equal to end, then name was not found.
	return resource_map_.find(name) == resource_map_.end();
}

resource_ptr resource_manager::__load(stream_ptr stream)
{
	resource_ptr resource = resource_ptr(__create_new_resource(stream->get_name()));

	if (!resource)
	{
		console::warning("[ResourceManager]: Could not load resource '%s' from stream. Resource object was NULL.", stream->get_name().c_str());
		return aeon_empty_resource;
	}

	if(!resource->__load(stream))
	{
		console::warning("[ResourceManager]: Could not load resource '%s' from stream. Load failed.", stream->get_name().c_str());
		return aeon_empty_resource;
	}

	return resource;
}

void resource_manager::__mark_as_finalize(resource_ptr resource)
{
	std::lock_guard<std::mutex> lock(resource_queue_mutex_);
	resource_queue_.push(resource);
}

} //namespace aeon
