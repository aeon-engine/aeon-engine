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

#ifndef resourcemanager_h__
#define resourcemanager_h__

namespace aeon
{

class resource_manager
{
friend class resource;
public:
    typedef std::vector<resource_ptr> resources;
    typedef std::queue<resource_ptr> resource_queue;

    resource_manager();
    virtual ~resource_manager();

    resource_ptr load(stream_ptr stream);
    resource_ptr load(const std::string &name);

    bool unload(resource_ptr resource);
    bool unload(const std::string &name);

    int finalize_resources();

protected:
    bool __is_name_unique(const std::string &name);
    resource_ptr __load(stream_ptr stream);
    bool __unload(const std::string &name, resources::iterator itr);

    virtual resource * __create_new_resource(const std::string &name) = 0;

    void __add_to_finalize_queue(resource_ptr resource);

    std::uint64_t __get_unique_handle() { return ++last_resource_handle_; }

    resources::iterator __find_resource_by_name(const std::string &name);
    resources::iterator __find_resource_by_handle(std::uint64_t handle);

    resource_ptr __get_resource_by_name(const std::string &name);

    resources resources_;
    std::mutex resources_mutex_;

    resource_queue resource_queue_;
    std::mutex resource_queue_mutex_;

private:
    std::uint64_t last_resource_handle_;
};

} /* namespace aeon */

#endif /* resourcemanager_h__ */
