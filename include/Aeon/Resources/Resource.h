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
	enum class LoadState
	{
		Retrieving,				/**< enum Retrieving data from the stream. This would normally mean loading from disk. */
		ReadyForFinalize,		/**< enum Ready for upload to the GPU. Uploading must be done on the render thread. */
		Loaded,					/**< enum Loaded and ready for use. */
		Unloading,				/**< enum Unloading and freeing resources. This resource can no longer be used. */
	};

	Resource(ResourceManager *creator, const std::string &name);
	virtual ~Resource();

protected:
	virtual bool			__load(StreamPtr stream) = 0;
	virtual bool			__finalize() = 0;

	ResourceManager *		creator_;
	std::string				name_;

};

typedef std::shared_ptr<Resource> ResourcePtr;
typedef std::weak_ptr<Resource> ResourceWeakPtr;

#define AeonEmptyResource ResourcePtr()

} /* namespace Aeon */

#endif /* AeonResource_h__ */
