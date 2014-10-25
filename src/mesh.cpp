#include "stdafx.h"

namespace aeon
{

mesh::mesh(resource_manager *creator, const std::string &name,
           std::uint64_t handle) :
	resource(creator, name, handle)
{

}

mesh::~mesh()
{

}

bool mesh::__load_impl(stream_ptr stream)
{
	return true;
}

bool mesh::__unload_impl()
{
	return true;
}

bool mesh::__finalize_impl()
{
	// Do stuff on gpu thread
	return true;
}

} /* namespace aeon */
