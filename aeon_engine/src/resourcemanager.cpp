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

resource_manager::resource_manager() :
    last_resource_handle_(0)
{
}

resource_manager::~resource_manager()
{
}

resource_ptr resource_manager::load(aeon::streams::stream_ptr stream)
{
    if (!stream)
    {
        console::warning("[ResourceManager]: Could not load resource from "
            "stream. Stream was NULL.");
        return nullptr;
    }

    if (!stream->has_name())
    {
        console::warning("[ResourceManager]: Could not load resource from "
            "stream. Name was not set.");
        return nullptr;
    }

    console::debug("[ResourceManager]: Loading resource '%s' by stream.",
        stream->get_name().c_str());

    if (!__is_name_unique(stream->get_name()))
    {
        console::warning("[ResourceManager]: Could not load resource '%s' "
            "from stream. Name was not unique.", stream->get_name().c_str());
        return nullptr;
    }

    return __load(stream);
}

resource_ptr resource_manager::load(const std::string &name)
{
    console::debug("[ResourceManager]: Loading resource '%s' by name.",
        name.c_str());

    // Check if the resource was already loaded
    auto resource = __get_resource_by_name(name);

    if (resource)
        return resource;

    aeon::streams::file_stream_ptr filestream = std::make_shared<aeon::streams::file_stream>(name,
        aeon::streams::access_mode::read);

    if (!filestream)
    {
        console::warning("[ResourceManager]: Could not load resource '%s'. "
            "FileStream could not be made.", name.c_str());
        return nullptr;
    }

    if (!filestream->good())
    {
        console::warning("[ResourceManager]: Could not load resource '%s'. "
            "FileStream was bad.", name.c_str());
        return nullptr;
    }

    return __load(filestream);
}

bool resource_manager::unload(resource_ptr resource)
{
    if (!resource)
    {
        console::warning("[ResourceManager]: Resource given to unload was "
            "NULL.");
        return false;
    }

    std::lock_guard<std::mutex> lock(resources_mutex_);
    resources::iterator itr = __find_resource_by_handle(
        resource->get_handle());

    return __unload(resource->get_name(), itr);
}

bool resource_manager::unload(const std::string &name)
{
    std::lock_guard<std::mutex> lock(resources_mutex_);
    resources::iterator itr = __find_resource_by_name(name);

    return __unload(name, itr);
}

int resource_manager::finalize_resources()
{
    std::lock_guard<std::mutex> lock(resource_queue_mutex_);

    int count = 0;
    while (!resource_queue_.empty())
    {
        bool result = false;

        resource_ptr resource = resource_queue_.front();
        if (resource->get_state() == resource::state::ready_for_finalize)
            result = resource->__finalize();
        else if (resource->get_state() == resource::state::unloading)
            result = resource->__unload_impl();
        else
            console::warning("[ResourceManager]: Queued resource %s was not "
                "in finalize or unloading state.",
                resource->get_name().c_str());

        if (!result)
        {
            console::warning("[ResourceManager]: Queued resource %s reported "
                "an error while finalizing.", resource->get_name().c_str());
        }

        resource_queue_.pop();

        ++count;
    }

    if (count > 0)
        console::debug("[ResourceManager]: Finalized %u resources.", count);

    return count;
}

bool resource_manager::__is_name_unique(const std::string &name)
{
    std::lock_guard<std::mutex> lock(resources_mutex_);

    // If the result of find is equal to end, then name was not found.
    return __find_resource_by_name(name) == resources_.end();
}

resource_ptr resource_manager::__load(aeon::streams::stream_ptr stream)
{
    resource_ptr resource = resource_ptr(__create_new_resource(
        stream->get_name()));

    if (!resource)
    {
        console::warning("[ResourceManager]: Could not load resource '%s' "
            "from stream. Resource object was NULL.",
            stream->get_name().c_str());
        return nullptr;
    }

    if (!resource->__load(stream))
    {
        console::warning("[ResourceManager]: Could not load resource '%s' "
            "from stream. Load failed.", stream->get_name().c_str());
        return nullptr;
    }

    resources_mutex_.lock();
    resources_.push_back(resource);
    resources_mutex_.unlock();

    __add_to_finalize_queue(resource);

    return resource;
}

bool resource_manager::__unload(const std::string &name,
                                resources::iterator itr)
{
    if (itr == resources_.end())
    {
        console::warning("[ResourceManager]: Resource '%s' was already "
            "unloaded or is busy unloading.", name.c_str());
        return false;
    }

    resource_ptr r = *itr;
    if (!r->__unload())
    {
        console::warning("[ResourceManager]: Resource '%s' reported an error "
            "while trying to unload.", name.c_str());
        return false;
    }

    resources_.erase(itr);
    __add_to_finalize_queue(r);

    return true;
}

void resource_manager::__add_to_finalize_queue(resource_ptr resource)
{
    std::lock_guard<std::mutex> lock(resource_queue_mutex_);
    resource_queue_.push(resource);
}

resource_manager::resources::iterator
    resource_manager::__find_resource_by_name(const std::string &name)
{
    resources::iterator itr = std::find_if(
        resources_.begin(),
        resources_.end(),
        [name](const resource_ptr s)
        {
            return s->get_name() == name;
        }
    );

    return itr;
}

resource_manager::resources::iterator
    resource_manager::__find_resource_by_handle(std::uint64_t handle)
{
    resources::iterator itr = std::find_if(
        resources_.begin(),
        resources_.end(),
        [handle](const resource_ptr s)
        {
            return s->get_handle() == handle;
        }
    );

    return itr;
}

resource_ptr resource_manager::__get_resource_by_name(const std::string &name)
{
    std::lock_guard<std::mutex> lock(resources_mutex_);

    // Check if this resource was already loaded before.
    resources::iterator itr = __find_resource_by_name(name);

    if (itr != resources_.end())
    {
        resource_ptr resource_ptr = *itr;

        if (resource_ptr)
        {
            console::debug("[ResourceManager]: Resource '%s' was already "
                "loaded.", name.c_str());

            return resource_ptr;
        }

        console::debug("[ResourceManager]: Resource '%s' no longer exists. "
            "Removing old reference and reloading.", name.c_str());
        resources_.erase(itr);
    }

    return nullptr;
}

} // namespace aeon
