#include "Aeon/Aeon.h"
#include "Aeon/Game.h"
#include "Aeon/GameState.h"

namespace Aeon
{

Game::Game()
:
current_gamestate_(NULL)
{

}

Game::~Game()
{

}

void Game::set_gamestate(GameStatePtr gamestate)
{
	if(current_gamestate_)
		current_gamestate_->on_leave();

	current_gamestate_ = gamestate;

	current_gamestate_->on_enter();
}

} //namespace Aeon
