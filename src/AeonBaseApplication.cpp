#include "AeonBaseApplication.h"
#include "AeonGame.h"

namespace Aeon
{

BaseApplication::BaseApplication(Game &game)
:
m_game(game)
{

}

BaseApplication::~BaseApplication()
{

}

void BaseApplication::initialize()
{
	__initialize();
	m_game.on_initialize();
}

void BaseApplication::cleanup()
{
	__cleanup();
	m_game.on_cleanup();
}

void BaseApplication::run()
{
	__run();
}

void BaseApplication::stop()
{
	m_game.on_stop();
	__stop();
}

} //namespace Aeon
