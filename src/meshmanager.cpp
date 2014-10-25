#include "stdafx.h"

aeon_initialize_singleton(aeon::mesh_manager);

namespace aeon
{

mesh_manager::mesh_manager()
{
	console::debug("[MeshManager]: created.");
}

mesh_manager::~mesh_manager()
{
	console::debug("[MeshManager]: disposed.");
}

mesh_ptr mesh_manager::load(stream_ptr stream)
{
	return std::dynamic_pointer_cast<mesh>(resource_manager::load(stream));
}

mesh_ptr mesh_manager::load(const std::string &name)
{
	return std::dynamic_pointer_cast<mesh>(resource_manager::load(name));
}

resource * mesh_manager::__create_new_resource(const std::string &name)
{
	return new mesh(this, name, __get_unique_handle());
}

} /* namespace aeon */
