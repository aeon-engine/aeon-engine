#include "aeon/aeon.h"
#include "aeon/root.h"
#include "aeon/console/console.h"
#include "aeon/resources/imagecodecmanager.h"
#include "aeon/resources/imagecodecpng.h"
#include "aeon/resources/texturemanager.h"

namespace aeon
{

aeon_initialize_singleton(root);

root::root(platforms::base_platform_ptr platform)
:
initialized_(false),
running_(false)
{
	platform_ = platform;
}

root::~root()
{

}

bool root::initialize(platforms::base_platform_ptr platform)
{
	if(!instance_)
	{
		root *r = new root(platform);
		if (!r)
		{
			console::info("[Root] Could not create Root.");
			return false;
		}

		return r->__initialize_impl(platform);
	}

	console::error("[Root] Can not initialize. Initialize was already called.");
	return false;
}

void root::run()
{
	if (!initialized_)
	{
		console::error("[Root] Can't run without initializing.");
		return;
	}

	//TODO: Implement dt
	float dt = 0.1f;

	running_ = true;
	while (running_)
	{
		if(!platform_->pre_frame())
			break;

		for(framelistener *framelistener : frame_listeners_)
		{
			framelistener->on_frame(dt);
		}

		for(framelistener *framelistener : frame_listeners_)
		{
			framelistener->on_render();
		}

		if(!platform_->post_frame())
			break;
	}

	if(!platform_->dispose())
		console::error("[Root] Platform reported an error while disposing.");

	image_codec_manager::dispose();
	texture_manager::dispose();

	running_ = false;
	initialized_ = false;
}

void root::stop()
{
	running_ = false;
}

void root::add_frame_listener(framelistener *listener)
{
	frame_listeners_.push_back(listener);
}

void root::remove_frame_listener(framelistener *listener)
{
	frame_listeners_.remove(listener);
}

void root::remove_all_frame_listeners()
{
	console::debug("[Root] Removing all frame listeners.");
	frame_listeners_.clear();
}

bool root::__initialize_impl(platforms::base_platform_ptr platform)
{
	if (initialized_)
	{
		console::warning("[Root] Already initialized. Can not initialize twice.");
		return false;
	}

	console::info("[Root] Initializing.");

	if (!platform_)
	{
		console::error("[Root] Could not create platform.");
		return false;
	}

	console::info("[Root] Initializing platform.");

	if (!platform_->initialize())
	{
		console::error("[Root] Failed to initialize platform.");
		return false;
	}

	console::info("[Root] Initializing glew.");

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		console::error("[Root] Failed to initialize glew: %s", glewGetErrorString(err));
		return false;
	}

	//TODO: Should we check if the singletons were properly created?
	//Register codecs
	image_codec_manager::create();

#ifdef AEON_USE_PNG
	image_codec_manager::get_singleton().register_codec(std::make_shared<image_codec_png>());
#endif

	texture_manager::create();

	initialized_ = true;
	return true;
}

} /* namespace aeon */
