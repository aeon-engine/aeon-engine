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

#ifndef resource_h__
#define resource_h__

namespace aeon
{

class resource_manager;
class resource
{
friend class resource_manager;
public:
    enum class state
    {
        empty               = 0, /**< Default state. */
        retrieving          = 0, /**< Retrieving data from the stream. This 
                                      would normally mean loading from disk. */
        ready_for_finalize  = 1, /**< Ready for upload to the GPU. Uploading 
                                      must be done on the render thread. */
        loaded              = 2, /**< Loaded and ready for use. */
        unloading           = 3, /**< Texture waiting for the resource manager 
                                      to free the handle. This resource can no 
                                      longer be used. */
        unloaded            = 4, /**< Unloading and freeing resources. This 
                                      resource can no longer be used. */
    };

    resource(resource_manager *creator, const std::string &name,
             std::uint64_t handle);
    virtual ~resource();

    state get_state() { return state_; }
    const std::string & get_name() { return name_; }
    std::uint64_t get_handle() { return handle_; }

protected:
    bool __load(stream_ptr stream);
    virtual bool __load_impl(stream_ptr stream) = 0;

    bool __unload();
    virtual bool __unload_impl() = 0;

    bool __finalize();
    virtual bool __finalize_impl() = 0;

    resource_manager *creator_;
    std::string name_;
    std::uint64_t handle_;
    std::atomic<state> state_;
};

typedef std::shared_ptr<resource> resource_ptr;

} /* namespace aeon */

#endif /* resource_h__ */
