#ifndef AeonResource_h__
#define AeonResource_h__

#include "Aeon/Streams/Stream.h"

namespace Aeon
{
class ResourceManager;
class Resource
{
friend class ResourceManager;
public:
	enum class State
	{
		Empty				= 0, /**< enum Default state. */
		Retrieving			= 0, /**< enum Retrieving data from the stream. This would normally mean loading from disk. */
		ReadyForFinalize	= 1, /**< enum Ready for upload to the GPU. Uploading must be done on the render thread. */
		Loaded				= 2, /**< enum Loaded and ready for use. */
		Unloading			= 3, /**< enum Texture waiting for the resource manager to free the handle. This resource can no longer be used. */
		Unloaded			= 4, /**< enum Unloading and freeing resources. This resource can no longer be used. */
	};

	Resource(ResourceManager *creator, const std::string &name);
	virtual ~Resource();

protected:
	bool					__load(StreamPtr stream);
	virtual bool			__load_impl(StreamPtr stream) = 0;

	bool					__unload();
	virtual bool			__unload_impl() = 0;

	bool					__finalize();
	virtual bool			__finalize_impl() = 0;

	ResourceManager *		creator_;
	std::string				name_;
	State					state_;
};

typedef std::shared_ptr<Resource> ResourcePtr;
typedef std::weak_ptr<Resource> ResourceWeakPtr;

#define AeonEmptyResource ResourcePtr()

} /* namespace Aeon */

#endif /* AeonResource_h__ */
