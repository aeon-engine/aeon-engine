#include "aeon/aeon.h"
#include "aeon/game.h"
#include "aeon/gamestate.h"

namespace aeon
{

game::game()
:
current_gamestate_(NULL)
{

}

game::~game()
{

}

void game::set_gamestate(game_state_ptr gamestate)
{
    if(current_gamestate_)
        current_gamestate_->on_leave();

    current_gamestate_ = gamestate;

    current_gamestate_->on_enter();
}

} /* namespace aeon */
