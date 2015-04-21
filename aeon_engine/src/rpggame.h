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

#ifndef rpggame_h__
#define rpggame_h__

namespace aeon
{

class game_state_game;

class rpg_game : public game
{
public:
    rpg_game();
    ~rpg_game();

protected:
    bool on_initialize();
    void on_run();
    void on_stop();
    void on_cleanup();

    game_state_ptr gamestate_game_;
};

} // namespace aeon

#endif // rpggame_h__
