/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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

aeon_utility_initialize_singleton(aeon::mesh_manager);

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

mesh_ptr mesh_manager::load(aeon::streams::stream_ptr stream)
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

} // namespace aeon
