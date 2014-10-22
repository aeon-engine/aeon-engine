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

} /* namespace aeon */

#endif /* gamestate_game_h__ */
