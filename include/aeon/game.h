#ifndef game_h__
#define game_h__

#include "aeon/gameState.h"

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

} //namespace aeon

#endif // game_h__
