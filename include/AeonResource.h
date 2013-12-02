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
	ResourceManager *		m_creator;
	std::string				m_name;
	Handle					m_handle;

};

typedef std::shared_ptr<Resource> ResourcePtr;
#define EMPTY_RESOURCE ResourcePtr()

} //namespace Aeon

#endif // AeonResource_h__
