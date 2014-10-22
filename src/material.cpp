#include "stdafx.h"

namespace aeon
{

material::material(resource_manager *creator, const std::string &name,
    std::uint64_t handle) :
    resource(creator, name, handle)
{

}

material::~material()
{

}

bool material::__load_impl(stream_ptr stream)
{
    // Load
    return true;
}

bool material::__unload_impl()
{
    // Unload

    return true;
}

bool material::__finalize_impl()
{
    // Do stuff on gpu thread
    return true;
}

} /* namespace aeon */
