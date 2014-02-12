#include "Aeon.h"
#include "AeonGame.h"
#include "AeonGameState.h"

namespace Aeon
{

Game::Game()
:
m_application(NULL),
m_current_gamestate(NULL)
{

}

Game::~Game()
{

}

bool Game::on_update(float dt)
{
	if (!m_current_gamestate)
		return true;

	return m_current_gamestate->on_update(dt);
}

void Game::on_render()
{
	if (!m_current_gamestate)
		return;

	m_current_gamestate->on_render();
}

void Game::set_gamestate(GameStatePtr gamestate)
{
	if(m_current_gamestate)
		m_current_gamestate->on_leave();

	m_current_gamestate = gamestate;

	m_current_gamestate->on_enter();
}

void Game::__register_application(BaseApplication *application)
{
	m_application = application;
}

} //namespace Aeon
