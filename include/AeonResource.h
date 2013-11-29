#ifndef AeonResource_h__
#define AeonResource_h__

namespace Aeon
{

class Resource
{
public:
	enum class Type
	{
		Image,
		Texture,
		Shader,
		Font
	};

	Resource(Type type)
	:
	m_loaded(false),
	m_type(type)
	{}

	virtual ~Resource() {}

	bool				loaded()		{ return m_loaded; }
	Type				get_type()		{ return m_type; }

	//This is called once after this resource was queued as completely loaded on the render thread.
	virtual void		finalize() {}

private:
	bool				m_loaded;
	Type				m_type;

protected:
	void				__set_loaded()	{ m_loaded = true; }
};

typedef std::shared_ptr<Resource>		ResourcePtr;
//Used in the resource manager. The resource manager itself should not be owner of a resource.
typedef std::weak_ptr<Resource>			ResourceWeakPtr;
	
#define EMPTY_RESOURCE	ResourcePtr()

} //namespace Aeon

#endif // AeonResource_h__
