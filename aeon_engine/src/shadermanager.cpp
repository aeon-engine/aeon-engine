/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2014 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#include "stdafx.h"

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
