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
