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

	for(FrameListener *framelistener : m_frame_listeners)
	{
		framelistener->on_frame(dt);
	}

	for(FrameListener *framelistener : m_frame_listeners)
	{
		framelistener->on_render();
	}
}

void Root::stop()
{

}

void Root::add_frame_listener(FrameListener *listener)
{
	m_frame_listeners.push_back(listener);
}

void Root::remove_frame_listener(FrameListener *listener)
{
	m_frame_listeners.remove(listener);
}

void Root::remove_all_frame_listeners()
{
	Console::debug("Removing all frame listeners.");
	m_frame_listeners.clear();
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
