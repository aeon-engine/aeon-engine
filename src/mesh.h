#ifndef mesh_h__
#define mesh_h__

namespace aeon
{

class mesh : public resource
{
public:
	mesh(resource_manager *creator, const std::string &name,
		 std::uint64_t handle);
	virtual ~mesh();

protected:
	virtual bool __load_impl(stream_ptr stream);
	virtual bool __unload_impl();
	virtual bool __finalize_impl();
};

typedef std::shared_ptr<mesh> mesh_ptr;

} /* namespace aeon */

#endif /* mesh_h__ */
