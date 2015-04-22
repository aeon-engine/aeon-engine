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

#ifndef gamestate_game_h__
#define gamestate_game_h__

namespace aeon
{

class game_state_game : public game_state
{
public:
    game_state_game();
    ~game_state_game();

    void on_enter();
    void on_leave();

    bool on_update(float dt);
    void on_render();
};

} // namespace aeon

#endif // gamestate_game_h__
