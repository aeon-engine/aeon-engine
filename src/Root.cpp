#include "Aeon/Aeon.h"
#include "Aeon/Root.h"
#include "Aeon/Console/Console.h"
#include "Aeon/Resources/ImageCodecManager.h"
#include "Aeon/Resources/ImageCodecPNG.h"
#include "Aeon/Resources/TextureManager.h"

namespace Aeon
{

AeonInitializeSingleton(Root);

Root::Root(Platforms::BasePlatformPtr platform)
:
initialized_(false),
running_(false)
{
	platform_ = platform;
}

Root::~Root()
{

}

bool Root::initialize(Platforms::BasePlatformPtr platform)
{
	if(!instance_)
	{
		Root *r = new Root(platform);
		if (!r)
		{
			Console::info("[Root] Could not create Root.");
			return false;
		}

		return r->__initialize_impl(platform);
	}

	Console::error("[Root] Can not initialize. Initialize was already called.");
	return false;
}

void Root::run()
{
	if (!initialized_)
	{
		Console::error("[Root] Can't run without initializing.");
		return;
	}

	//TODO: Implement dt
	float dt = 0.1f;

	running_ = true;
	while (running_)
	{
		if(!platform_->pre_frame())
			break;

		for(FrameListener *framelistener : frame_listeners_)
		{
			framelistener->on_frame(dt);
		}

		for(FrameListener *framelistener : frame_listeners_)
		{
			framelistener->on_render();
		}

		if(!platform_->post_frame())
			break;
	}

	if(!platform_->dispose())
		Console::error("[Root] Platform reported an error while disposing.");

	ImageCodecManager::dispose();
	TextureManager::dispose();

	running_ = false;
	initialized_ = false;
}

void Root::stop()
{
	running_ = false;
}

void Root::add_frame_listener(FrameListener *listener)
{
	frame_listeners_.push_back(listener);
}

void Root::remove_frame_listener(FrameListener *listener)
{
	frame_listeners_.remove(listener);
}

void Root::remove_all_frame_listeners()
{
	Console::debug("[Root] Removing all frame listeners.");
	frame_listeners_.clear();
}

bool Root::__initialize_impl(Platforms::BasePlatformPtr platform)
{
	if (initialized_)
	{
		Console::warning("[Root] Already initialized. Can not initialize twice.");
		return false;
	}

	Console::info("[Root] Initializing.");

	if (!platform_)
	{
		Console::error("[Root] Could not create platform.");
		return false;
	}

	if (!platform_->initialize())
	{
		Console::error("[Root] Failed to initialize platform.");
		return false;
	}

	//TODO: Should we check if the singletons were properly created?
	//Register codecs
	ImageCodecManager::create();

#ifdef AEON_USE_PNG
	ImageCodecManager::getSingleton().register_codec(std::make_shared<ImageCodecPNG>());
#endif

	TextureManager::create();

	initialized_ = true;
	return true;
}

} /* namespace Aeon */
