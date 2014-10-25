#ifndef meshmanager_h__
#define meshmanager_h__

namespace aeon
{

class mesh_manager : public resource_manager,
	public singleton<mesh_manager>
{
public:
	mesh_manager();
	virtual ~mesh_manager();

	mesh_ptr load(stream_ptr stream);
	mesh_ptr load(const std::string &name);

protected:
	resource *__create_new_resource(const std::string &name);
};

} /* namespace aeon */

#endif /* meshmanager_h__ */
