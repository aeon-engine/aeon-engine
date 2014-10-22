#include "stdafx.h"

aeon_initialize_singleton(aeon::material_manager);

namespace aeon
{

material_manager::material_manager()
{
    console::debug("[TextureManager]: created.");
}

material_manager::~material_manager()
{
    console::debug("[TextureManager]: disposed.");
}

material_ptr material_manager::load(stream_ptr stream)
{
    return std::dynamic_pointer_cast<material>(resource_manager::load(stream));
}

material_ptr material_manager::load(const std::string &name)
{
    return std::dynamic_pointer_cast<material>(resource_manager::load(name));
}

resource * material_manager::__create_new_resource(const std::string &name)
{
    return new material(this, name, __get_unique_handle());
}

} /* namespace aeon */
