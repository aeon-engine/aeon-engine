#include "Aeon/Aeon.h"
#include "Aeon/Root.h"
#include "Aeon/Console/Console.h"
#include "Aeon/Resources/ImageCodecManager.h"
#include "Aeon/Resources/ImageCodecPNG.h"
#include "Aeon/Resources/TextureManager.h"

namespace Aeon
{

Root::Root()
{
	__initialize();
}

Root::~Root()
{

}

void Root::render()
{

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

}

} //namespace Aeon

