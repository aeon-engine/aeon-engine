#include "Aeon/Aeon.h"
#include "Aeon/Root.h"

namespace Aeon
{

Root::Root(GamePtr game)
:
m_initialized(false)
{
	Console::debug("Aeon Root created.");

	//Register codecs
	ImageCodecManager::create();

#ifdef AEON_USE_PNG
	ImageCodecManager::getSingleton().register_codec(std::make_shared<ImageCodecPNG>());
#endif

	TextureManager::create();
}

Root::~Root()
{

}

void Root::render()
{

}

void Root::__initialize()
{

}

void Root::__cleanup()
{

}

} //namespace Aeon

