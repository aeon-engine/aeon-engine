#include "aeon/aeon.h"
#include "aeon/console/console.h"
#include "aeon/resources/shader.h"

namespace aeon
{

shader::shader(resource_manager *creator, const std::string &name, std::uint64_t handle)
:
resource(creator, name, handle),
texture_(0)
{

}

shader::~shader()
{

}

bool shader::__load_impl(stream_ptr stream)
{
	return true;
}

bool shader::__unload_impl()
{
	return true;
}

bool shader::__finalize_impl()
{
	return true;
}

} //namespace aeon
