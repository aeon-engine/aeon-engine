/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2014 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#include "stdafx.h"

namespace aeon
{

game::game() :
    current_gamestate_(nullptr)
{

}

game::~game()
{

}

void game::set_gamestate(game_state_ptr gamestate)
{
    if (current_gamestate_)
        current_gamestate_->on_leave();

    current_gamestate_ = gamestate;

    current_gamestate_->on_enter();
}

} /* namespace aeon */
