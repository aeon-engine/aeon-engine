#ifndef shadermanager_h__
#define shadermanager_h__

#include "aeon/resources/resourcemanager.h"
#include "aeon/utility/singleton.h"
#include "aeon/streams/stream.h"
#include "aeon/resources/shader.h"

namespace aeon
{

class shader_manager : public resource_manager, 
	public singleton<shader_manager>
{
public:
	shader_manager();
	virtual ~shader_manager();

	shader_ptr load(stream_ptr stream);
	shader_ptr load(const std::string &name);

protected:
	resource *__create_new_resource(const std::string &name);
};

} //namespace aeon

#endif // shadermanager_h__
