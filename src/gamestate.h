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

#ifndef gamestate_h__
#define gamestate_h__

namespace aeon
{

class game_state
{
public:
    game_state() {}
    virtual ~game_state() {}

    virtual void on_enter() = 0;
    virtual void on_leave() = 0;
};

typedef std::shared_ptr<game_state> game_state_ptr;

} /* namespace aeon */

#endif /* gamestate_h__ */
