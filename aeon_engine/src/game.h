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

#ifndef game_h__
#define game_h__

#include "gamestate.h"

namespace aeon
{

class game
{
public:
    game();
    virtual ~game();

    void set_gamestate(game_state_ptr gamestate);

protected:
    virtual bool on_initialize() = 0;
    virtual void on_run() = 0;
    virtual void on_stop() = 0;
    virtual void on_cleanup() = 0;

private:
    game_state_ptr current_gamestate_;
};

typedef std::shared_ptr<game> game_ptr;

} // namespace aeon

#endif // game_h__
