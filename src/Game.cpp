#include "Aeon/Aeon.h"
#include "Aeon/Game.h"
#include "Aeon/GameState.h"

namespace Aeon
{

Game::Game()
:
m_current_gamestate(NULL)
{

}

Game::~Game()
{

}

void Game::set_gamestate(GameStatePtr gamestate)
{
	if(m_current_gamestate)
		m_current_gamestate->on_leave();

	m_current_gamestate = gamestate;

	m_current_gamestate->on_enter();
}

} //namespace Aeon
