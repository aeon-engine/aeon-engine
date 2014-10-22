#include "stdafx.h"

aeon_initialize_singleton(aeon::texture_manager);

namespace aeon
{

texture_manager::texture_manager()
{
    console::debug("[TextureManager]: created.");
}

texture_manager::~texture_manager()
{
    console::debug("[TextureManager]: disposed.");
}

texture_ptr texture_manager::load(stream_ptr stream)
{
    return std::dynamic_pointer_cast<texture>(resource_manager::load(stream));
}

texture_ptr texture_manager::load(const std::string &name)
{
    return std::dynamic_pointer_cast<texture>(resource_manager::load(name));
}

resource * texture_manager::__create_new_resource(const std::string &name)
{
    return new texture(this, name, __get_unique_handle());
}

} /* namespace aeon */
