#include "stdafx.h"

namespace aeon
{

game_state_game::game_state_game()
{

}

game_state_game::~game_state_game()
{

}

void game_state_game::on_enter()
{
    console::debug("GameStateGame::on_enter()");
}

void game_state_game::on_leave()
{
    console::debug("GameStateGame::on_leave()");
}

bool game_state_game::on_update(float dt)
{
    //console::debug("GameStateGame::on_update(%f)", dt);
    return true;
}

void game_state_game::on_render()
{
    //console::debug("GameStateGame::on_render()");
}

} /* namespace aeon */
