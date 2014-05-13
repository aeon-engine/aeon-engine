#ifndef AeonResource_h__
#define AeonResource_h__

namespace Aeon
{

class ResourceManager;
class Resource
{
public:
	typedef unsigned long Handle;

	enum class LoadState
	{
		Unloaded,
		Preparing,
		Prepared,
		Loading,
		Loaded,
		Unloading,
	};

	Resource(ResourceManager *creator, const std::string &name, Handle handle);
	virtual ~Resource();

protected:
	ResourceManager *		creator_;
	std::string				name_;
	Handle					handle_;

};

typedef std::shared_ptr<Resource> ResourcePtr;
#define AeonEmptyResource ResourcePtr()

} //namespace Aeon

#endif // AeonResource_h__
