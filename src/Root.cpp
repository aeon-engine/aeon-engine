#include "Aeon/Aeon.h"
#include "Aeon/Root.h"
#include "Aeon/Console/Console.h"
#include "Aeon/Resources/ImageCodecManager.h"
#include "Aeon/Resources/ImageCodecPNG.h"
#include "Aeon/Resources/TextureManager.h"

namespace Aeon
{

AeonInitializeSingleton(Root);

Root::Root()
{
	__initialize();
}

Root::~Root()
{

}

void Root::render()
{
	//TODO: Implement dt
	float dt = 0.1f;

	for(FrameListener *framelistener : frame_listeners_)
	{
		framelistener->on_frame(dt);
	}

	for(FrameListener *framelistener : frame_listeners_)
	{
		framelistener->on_render();
	}
}

void Root::stop()
{

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
	Console::debug("Removing all frame listeners.");
	frame_listeners_.clear();
}

void Root::__initialize()
{
	Console::debug("Aeon Root created.");

	//Register codecs
	ImageCodecManager::create();

#ifdef AEON_USE_PNG
	ImageCodecManager::getSingleton().register_codec(std::make_shared<ImageCodecPNG>());
#endif

	TextureManager::create();
}

void Root::__cleanup()
{
	ImageCodecManager::dispose();
	TextureManager::dispose();
}

} //namespace Aeon
