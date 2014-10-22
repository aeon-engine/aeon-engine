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

} /* namespace aeon */

#endif /* rpggame_h__ */
