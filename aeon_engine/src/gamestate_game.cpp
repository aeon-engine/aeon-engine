/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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

} // namespace aeon
