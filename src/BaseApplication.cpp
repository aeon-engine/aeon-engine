#include "Aeon/Aeon.h"
#include "Aeon/BaseApplication.h"
#include "Aeon/Game.h"
#include "Aeon/Console/Console.h"
#include "Aeon/Resources/ImageCodecManager.h"
#include "Aeon/Resources/ImageCodecPNG.h"
#include "Aeon/Resources/TextureManager.h"

namespace Aeon
{

BaseApplication::BaseApplication()
:
m_game(NULL),
m_initialized(false)
{
	Console::debug("BaseApplication created.");

	//Register codecs
	ImageCodecManager::create();

#ifdef AEON_USE_PNG
	ImageCodecManager::getSingleton().register_codec(std::make_shared<ImageCodecPNG>());
#endif

	TextureManager::create();
}

BaseApplication::~BaseApplication()
{
	Console::debug("BaseApplication disposed.");

	ImageCodecManager::dispose();
	TextureManager::dispose();
}

bool BaseApplication::initialize(GamePtr game)
{
	if(!game)
		return false;

	m_game = game;

	if(!__initialize())
		return false;

	m_initialized = true;

	return true;
}

void BaseApplication::cleanup()
{
	__cleanup();

	m_game = NULL;
	m_initialized = NULL;
}

void BaseApplication::run()
{
	if(!m_initialized)
	{
		Console::warning("BaseApplication::run called without being initialized.");
		return;
	}

	Console::debug("BaseApplication::run called. Entering render loop.");

	if(!m_game)
	{
		Console::fatal("Could not run application. No game found!");
		return;
	}

	__run();
}

void BaseApplication::stop()
{
	Console::debug("BaseApplication::stop called.");
	__stop();
}

void BaseApplication::__handle_events()
{
	TextureManager::getSingleton().finalize_textures();
}

} //namespace Aeon
