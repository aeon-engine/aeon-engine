#ifndef AeonGameState_h__
#define AeonGameState_h__

namespace Aeon
{

class GameState
{
public:
	GameState() {}
	virtual ~GameState() {}

	virtual void			on_enter() = 0;
	virtual void			on_leave() = 0;
};

typedef std::shared_ptr<GameState> GameStatePtr;

}

#endif // AeonGameState_h__
