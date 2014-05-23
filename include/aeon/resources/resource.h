#ifndef resource_h__
#define resource_h__

#include "aeon/streams/stream.h"

namespace aeon
{
class resource_manager;
class resource
{
friend class resource_manager;
public:
	enum class state
	{
		empty				= 0, /**< enum Default state. */
		retrieving			= 0, /**< enum Retrieving data from the stream. This would normally mean loading from disk. */
		ready_for_finalize	= 1, /**< enum Ready for upload to the GPU. Uploading must be done on the render thread. */
		loaded				= 2, /**< enum Loaded and ready for use. */
		unloading			= 3, /**< enum Texture waiting for the resource manager to free the handle. This resource can no longer be used. */
		unloaded			= 4, /**< enum Unloading and freeing resources. This resource can no longer be used. */
	};

	resource(resource_manager *creator, const std::string &name);
	virtual ~resource();

	state					get_state() { return state_; }
	const std::string &		get_name()	{ return name_; }

protected:
	bool					__load(stream_ptr stream);
	virtual bool			__load_impl(stream_ptr stream) = 0;

	bool					__unload();
	virtual bool			__unload_impl() = 0;

	bool					__finalize();
	virtual bool			__finalize_impl() = 0;

	resource_manager *		creator_;
	std::string				name_;
	std::atomic<state>		state_;
};

typedef std::shared_ptr<resource> resource_ptr;

#define aeon_empty_resource resource_ptr()

} //namespace aeon

#endif // resource_h__
