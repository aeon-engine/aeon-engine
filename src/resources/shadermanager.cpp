#include "aeon/stdafx.h"

aeon_initialize_singleton(aeon::shader_manager);

namespace aeon
{

shader_manager::shader_manager()
{
    console::debug("[ShaderManager]: created.");
}

shader_manager::~shader_manager()
{
    console::debug("[ShaderManager]: disposed.");
}

shader_ptr shader_manager::load(stream_ptr stream)
{
    return std::dynamic_pointer_cast<shader>(resource_manager::load(stream));
}

shader_ptr shader_manager::load(const std::string &name)
{
    return std::dynamic_pointer_cast<shader>(resource_manager::load(name));
}

resource * shader_manager::__create_new_resource(const std::string &name)
{
    return new shader(this, name, __get_unique_handle());
}

} /* namespace aeon */
