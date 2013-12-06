#include "Aeon.h"
#include "AeonBaseApplication.h"
#include "AeonGame.h"
#include "AeonConsole.h"

namespace Aeon
{

BaseApplication::BaseApplication()
:
m_game(NULL),
m_initialized(false)
{

}

BaseApplication::~BaseApplication()
{

}

bool BaseApplication::initialize(GamePtr game)
{
	if(!game)
		return false;

	m_game = game;

	if(!__initialize())
		return false;

	//TODO: If this fails, should we call cleanup on the Application?
	if(!m_game->on_initialize())
		return false;

	m_game->__register_application(this);

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

	m_game->on_run();

	__run();
}

void BaseApplication::stop()
{
	Console::debug("BaseApplication::stop called.");

	if(m_game != NULL)
		m_game->on_stop();

	__stop();
}

} //namespace Aeon
