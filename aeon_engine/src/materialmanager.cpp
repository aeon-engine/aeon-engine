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

aeon_initialize_singleton(aeon::material_manager);

namespace aeon
{

material_manager::material_manager()
{
    console::debug("[MaterialManager]: created.");
}

material_manager::~material_manager()
{
    console::debug("[MaterialManager]: disposed.");
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
