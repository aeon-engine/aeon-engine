#ifndef texture_h__
#define texture_h__

#include "aeon/resources/resource.h"
#include "aeon/streams/stream.h"
#include "aeon/resources/image.h"

namespace aeon
{

class texture : public resource
{
public:
	texture(resource_manager *creator, const std::string &name);
	virtual ~texture();

protected:
	virtual bool			__load_impl(stream_ptr stream);
	virtual bool			__unload_impl();
	virtual bool			__finalize_impl();

	image_ptr				image_;
	GLuint					texture_;
};

typedef std::shared_ptr<texture> texture_ptr;
#define aeon_empty_texture texture_ptr()

} //namespace aeon

#endif // texture_h__
