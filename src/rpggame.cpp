#include "stdafx.h"

namespace aeon
{

rpg_game::rpg_game()
    :
    gamestate_game_(std::make_shared<game_state_game>())
{

}

rpg_game::~rpg_game()
{

}

bool rpg_game::on_initialize()
{
    console::debug("RPGGame::on_initialize()");

    return true;
}

void rpg_game::on_run()
{
    console::debug("RPGGame::on_run()");

    set_gamestate(gamestate_game_);
}

void rpg_game::on_stop()
{
    console::debug("RPGGame::on_stop()");
}

void rpg_game::on_cleanup()
{
    console::debug("RPGGame::on_cleanup()");
}

} /* namespace aeon */
