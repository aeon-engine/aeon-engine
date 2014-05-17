#ifndef AeonGame_h__
#define AeonGame_h__

#include "Aeon/GameState.h"

namespace Aeon
{

class Game
{
public:
	Game();
	virtual ~Game();

	void					set_gamestate(GameStatePtr gamestate);

protected:
	virtual bool			on_initialize() = 0;
	virtual void			on_run() = 0;
	virtual void			on_stop() = 0;
	virtual void			on_cleanup() = 0;

private:
	GameStatePtr			current_gamestate_;
};

typedef std::shared_ptr<Game> GamePtr;

} //namespace Aeon

#endif /* AeonGame_h__ */
