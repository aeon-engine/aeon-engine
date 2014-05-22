#include "Aeon/Aeon.h"
#include "Aeon/Resources/ResourceManager.h"
#include "Aeon/Console/Console.h"
#include "Aeon/Streams/FileStream.h"

namespace Aeon
{

ResourceManager::ResourceManager()
{
	Console::debug("[ResourceManager]: created.");
}

ResourceManager::~ResourceManager()
{
	Console::debug("[ResourceManager]: disposed.");
}

ResourcePtr ResourceManager::load(StreamPtr stream)
{
	if (!stream)
	{
		Console::warning("[ResourceManager]: Could not load resource from stream. Stream was NULL.");
		return AeonEmptyResource;
	}

	if (!stream->has_name())
	{
		Console::warning("[ResourceManager]: Could not load resource from stream. Name was not set.");
		return AeonEmptyResource;
	}

	Console::debug("[ResourceManager]: Loading resource '%s' by stream.", stream->get_name().c_str());

	if (!__is_name_unique(stream->get_name()))
	{
		Console::warning("[ResourceManager]: Could not load resource '%s' from stream. Name was not unique.", stream->get_name().c_str());
		return AeonEmptyResource;
	}

	return __load(stream);
}

ResourcePtr ResourceManager::load(const std::string &name)
{
	std::lock_guard<std::mutex> lock(resource_map_mutex_);

	Console::debug("[ResourceManager]: Loading resource '%s' by name.", name.c_str());

	//Check if this resource was already loaded before.
	ResourceMap::iterator itr = resource_map_.find(name);

	if (itr != resource_map_.end())
	{
		ResourceWeakPtr weak_resource_ptr = itr->second;
		ResourcePtr resource_ptr = weak_resource_ptr.lock();

		if (resource_ptr)
		{
			Console::debug("[ResourceManager]: Resource '%s' was already loaded.", name.c_str());
			return resource_ptr;
		}

		Console::debug("[ResourceManager]: Resource '%s' no longer exists. Removing old reference and reloading.", name.c_str());
		resource_map_.erase(itr);
	}

	FileStreamPtr filestream = std::make_shared<FileStream>(name, Stream::AccessMode::Read);

	if (!filestream)
	{
		Console::warning("[ResourceManager]: Could not load resource '%s'. FileStream could not be made.", name.c_str());
		return AeonEmptyResource;
	}

	if (!filestream->good())
	{
		Console::warning("[ResourceManager]: Could not load resource '%s'. FileStream was bad.", name.c_str());
		return AeonEmptyResource;
	}

	return __load(filestream);
}

int ResourceManager::finalize_resources()
{
	std::lock_guard<std::mutex> lock(resource_queue_mutex_);
	
	int count = 0;
	while(!resource_queue_.empty())
	{
		ResourcePtr resource = resource_queue_.front();
		if (resource->get_state() == Resource::State::ReadyForFinalize)
			resource->__finalize();
		else if (resource->get_state() == Resource::State::Unloading)
			resource->__unload();
		else
			Console::warning("[ResourceManager]: Queued resource %s was not in finalize or unloading state.", resource->get_name().c_str());

		resource_queue_.pop();

		++count;
	}

	return count;
}

bool ResourceManager::__is_name_unique(const std::string &name)
{
	std::lock_guard<std::mutex> lock(resource_map_mutex_);

	//If the result of find is equal to end, then name was not found.
	return resource_map_.find(name) == resource_map_.end();
}

ResourcePtr ResourceManager::__load(StreamPtr stream)
{
	ResourcePtr resource = ResourcePtr(__create_new_resource(stream->get_name()));

	if (!resource)
	{
		Console::warning("[ResourceManager]: Could not load resource '%s' from stream. Resource object was NULL.", stream->get_name().c_str());
		return AeonEmptyResource;
	}

	if(!resource->__load(stream))
	{
		Console::warning("[ResourceManager]: Could not load resource '%s' from stream. Load failed.", stream->get_name().c_str());
		return AeonEmptyResource;
	}

	return resource;
}

void ResourceManager::__mark_as_finalize(ResourcePtr resource)
{
	std::lock_guard<std::mutex> lock(resource_queue_mutex_);
	resource_queue_.push(resource);
}

} /* namespace Aeon */
