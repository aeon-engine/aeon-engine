#ifndef shader_h__
#define shader_h__

#include "aeon/resources/resource.h"
#include "aeon/streams/stream.h"

namespace aeon
{

class shader : public resource
{
public:
	shader(resource_manager *creator, const std::string &name, std::uint64_t handle);
	virtual ~shader();

protected:
	virtual bool			__load_impl(stream_ptr stream);
	virtual bool			__unload_impl();
	virtual bool			__finalize_impl();

	GLuint					texture_;
};

typedef std::shared_ptr<shader> shader_ptr;
#define aeon_empty_shader shader_ptr()

} //namespace aeon

#endif // shader_h__
