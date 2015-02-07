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
